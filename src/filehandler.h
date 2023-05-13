#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include "custom_definitions.h"
#include "pyclustering/cluster/cluster_data.hpp"
#include <filesystem>
#include <algorithm>
#include <math.h>
namespace fs = std::filesystem;
using namespace std;
class FileHandler
{
public:


    FileHandler(const string &path,const bool &tsv);
    FileHandler(const string &path,const string &columnPath,const bool &tsv);

    FileHandler();
    FileHandler(const stringset &content, const stringvec &cols);

    stringset read_file(const string &path,const bool &tsv);
    stringvec getCols();
    stringset getContents();
    void write(const string &path);
    void write(const string &path,const string &col_path);
    pyclustering::dataset toDataset(const stringset &input);
    void dropZeroCols(pyclustering::dataset & ds);
    bool isFileAt(const string &Fpath);
    bool couldread;
    void dropCols(const stringvec & cols);
    void useClusters(const string & colname);
    void classify(const string &clname, const stringvec &clc);
    void setColumnNames(const stringvec &colNames);
    void autoNamer();
    void cleanUpColNames();
    stringvec getClusters();
private:
    string path;
    stringvec column_names;
    stringset content;
    string clusterName;
    stringvec clusterColumn;

};

#endif 
