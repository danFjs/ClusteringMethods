#include "filehandler.h"


FileHandler::FileHandler(){

}
void FileHandler::cleanUpColNames(){
    for (int var = 0; var < column_names.size(); ++var) {
        for (int index = 0; index < column_names[var].size(); ++index) {
            char c = column_names[var][index];
            if(c == '"' || c == ' ' || c == '\r' || c=='\t' || c=='\n' ){
                column_names[var].erase(column_names[var].begin()+index);
                index--;
            }

        }
    }
}

stringvec FileHandler::getClusters()
{
    return this->clusterColumn;
}

bool FileHandler::isFileAt(const string &Fpath){
    ifstream f(Fpath.c_str());
    return f.good();

}
FileHandler::FileHandler(const string &path,const bool &tsv)
{
 
    stringset content = read_file(path,tsv);
    this->column_names = content[0];
    cleanUpColNames();
    if(content.size()>0){

        content.erase(content.begin());
        this->content = content;
    }
}
FileHandler::FileHandler(const string &path,const string &columnPath,const bool &tsv)
{
   stringvec cnames;
   for(stringvec i : read_file(columnPath,tsv)){
        cnames.push_back(i[0]);
   }
   this->column_names = cnames;
   cleanUpColNames();
   stringset content = read_file(path,tsv);
   this->content = content;
}
FileHandler::FileHandler(const stringset &content, const stringvec &cols){
   this->content = content;
   this->column_names =cols;
    cleanUpColNames();
}
stringset FileHandler::read_file(const string &path,const bool &tsv){
    stringset content;
    stringvec row;
    string line, word;
    fstream file (path, ios::in);
    if(file.is_open())
    {
        while(getline(file, line))
        {
            row.clear();
            stringstream str(line);

            if(tsv){
                while(getline(str, word,'\t'))
                    row.push_back(word);
                content.push_back(row);
            }else{
                while(getline(str, word,','))
                    row.push_back(word);
                content.push_back(row);
            }


        }couldread = true;
    }else{
        couldread = false;
    }
    file.close();
    return content;

}

stringvec FileHandler::getCols(){
    return this->column_names;
};
stringset FileHandler::getContents(){
    return this->content;
};
void FileHandler::useClusters(const string &colname){

    using namespace pyclustering::clst;
    this->clusterName = colname;
    int colIndex=-1;
    for (int i = 0; i < this->column_names.size(); ++i) {
        if(column_names[i]==colname){
            column_names.erase(column_names.begin()+i);
            colIndex = i;
        }

    }
    if(colIndex==-1){
        throw runtime_error("error in useClusters");
    }
    for (int j = 0; j < content.size(); ++j) {

        this->clusterColumn.push_back(content[j][colIndex]);
        this->content[j].erase(content[j].begin()+colIndex);
    }
}
void FileHandler::classify(const string &clname, const stringvec &clc){
    this->clusterName = clname;
    this->clusterColumn=clc;
}
void FileHandler::write(const string &path){
    ofstream file(path);
    if(file.is_open())
    {
        for(const string &data : this->getCols()){
            file<<data;
            if(data!=this->getCols().back()){
                file<<",";
            }

        }
        file<<"\n";
    for(stringvec i : this->content){
        for(const string &data : i){
            file<<data;
            if(data!=i.back()){
                file<<",";
            }

        }
        if(i!=this->content.back()){
            file<<"\n";
        }
        file.flush();
    }
    file.close();
    }
}

void FileHandler::write(const string &path,const string &cpath){
    ofstream file(path);
    ofstream col(cpath);
    if(col.is_open())
    {
        for(const string &data : this->getCols()){
            col<<data;
            if(data!=this->getCols().back()){
               col<<"\n";
            }

        }

    }
    if(file.is_open()){
        for(stringvec i : this->content){
            for(const string &data : i){
                file<<data;
                if(data!=i.back()){
                    file<<",";
                }

            }
            if(i!=this->content.back()){
                file<<"\n";
            }
            file.flush();
        }
        file.close();
    }

}
pyclustering::dataset FileHandler::toDataset(const stringset &input){
    pyclustering::dataset * dataset = new pyclustering::dataset();
    for(int i = 0; i< input.size();++i){
        vector<double> dubloon;
        for(int j = 0; j< input[i].size();++j){
            double d;
            try{
                std::istringstream number_stream(input[i][j]);
                number_stream >> d;
            }
            catch(exception e){
            d = std::numeric_limits<double>::quiet_NaN() ;
            }
            dubloon.push_back(d);
        }
        dataset->push_back(dubloon);

    }
    return *dataset;
}

void FileHandler::dropCols(const stringvec & cols){
    for (int i = 0; i < cols.size(); ++i) {

        for (int j = 0; j < column_names.size(); ++j) {
            if(column_names[j]==cols[i]){

               this->column_names.erase(this->column_names.begin()+j);

                for (int k = 0; k < content.size(); ++k) {
                    this->content[k].erase(this->content[k].begin()+j);
                }

            }
        }
    }

}
void FileHandler::setColumnNames(const stringvec &colNames){
    this->column_names = colNames;
}
void FileHandler::autoNamer(){
    for (int i = 0; i < content[0].size(); ++i) {
        this->column_names.push_back(std::to_string(i));
    }
}
