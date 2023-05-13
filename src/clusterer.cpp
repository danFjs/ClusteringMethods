#include "clusterer.h"

Clusterer::Clusterer(const dataset &data)
{
    this->self_dataset = data;
}


gmeans_data Clusterer::run_gmeans(const size_t &p_repeat,
                                   const long long &p_kmax,
                                   const size_t &p_k_initial,
                                   const double &p_tolerance,
                                   const long long &p_random_state)
{
    gmeans p_model = gmeans(p_k_initial,p_tolerance,p_repeat,p_kmax,p_random_state);
    gmeans_data  p_result =  gmeans_data();

    p_model.process(self_dataset, p_result);
    return  p_result;
}


 xmeans_data Clusterer::run_xmeans(const dataset & p_initial_centers,
                                  const std::size_t p_kmax,
                                  const std::size_t p_repeat,
                                  const double p_tolerance,
                                  const splitting_type p_criterion,

                                  const long long p_random_state,
                                  const distance_metric<point> & p_metric)
 {

    xmeans * p_model = new xmeans(p_initial_centers,p_kmax,p_tolerance,p_criterion,p_repeat,p_random_state,p_metric);
    xmeans_data *p_result = new xmeans_data();
    p_model->process( self_dataset, *p_result);
    return *p_result;
}
 kmeans_data Clusterer::run_kmeans(const dataset & p_initial_centers,
                        const double p_tolerance,
                        const std::size_t p_itermax,
                        const distance_metric<point> & p_metric){
    kmeans * p_model = new kmeans(p_initial_centers,p_tolerance,p_itermax,p_metric);
    kmeans_data * p_result = new kmeans_data();
    p_model->process(self_dataset,*p_result);
    return *p_result;
 }


 dataset Clusterer::initialize_random_centers(const int &num, const long long random_state){
     random_center_initializer * rci = new random_center_initializer(num,random_state);
     dataset *p_ds = new dataset();
     rci->initialize(self_dataset,*p_ds);
     return *p_ds;
 }
 pointsetset Clusterer::toDisplayVals(const cluster_data &sets){
     vector<cluster> vcds = sets.clusters();
     pointsetset pss = pointsetset(vcds.size());
     pointset ps = toDisplayVals(self_dataset);
     for(int i = 0 ;i<vcds.size();i++){
         pointset temp = pointset(vcds[i].size());
         for(int j = 0; j<vcds[i].size(); j++){
             temp[j]=(ps[vcds[i][j]]);
         }
         pss[i] = (temp);
     }
     return pss;

 }
pointsetset Clusterer::toDisplayVals(const gmeans_data &sets){
    vector<cluster> vcds = sets.clusters();
    pointsetset pss = pointsetset(vcds.size());
    pointset ps = toDisplayVals(self_dataset);
    for(int i = 0 ;i<vcds.size();i++){
        pointset temp = pointset(vcds[i].size());
        for(int j = 0; j<vcds[i].size(); j++){
            temp[j]=(ps[vcds[i][j]]);
        }
        pss[i] = (temp);
    }
    return pss;

}

pointsetset Clusterer::toDisplayVals(const xmeans_data &sets){
    vector<cluster> vcds = sets.clusters();
    pointsetset pss = pointsetset(vcds.size());
    pointset ps = toDisplayVals(self_dataset);
    for(int i = 0 ;i<vcds.size();i++){
        pointset temp = pointset(vcds[i].size());
        for(int j = 0; j<vcds[i].size(); j++){
            temp[j]=(ps[vcds[i][j]]);
        }
        pss[i] = (temp);
    }
    return pss;
}

cluster_data Clusterer::usePredefinedClusters(const stringvec &classes)
{
    cluster_data * p_cd = new cluster_data();
    stringvec clnames;
    for (size_t i = 0; i < self_dataset.size(); ++i) {
        if (std::find(clnames.begin(), clnames.end(), classes[i]) == clnames.end()) {
            clnames.push_back(classes[i]);
            p_cd->clusters().push_back(*new cluster());
        }
        for (int var = 0; var < clnames.size(); ++var) {
            if(clnames[var] == classes[i]){
                p_cd->clusters()[var].push_back(i);
            }
        }


    }/*
    for (int var = 0; var < p_cd->clusters().size(); ++var) {
        for (int i = 0; i < p_cd->clusters()[var].size(); ++i) {
            cout<<p_cd->clusters()[var].at(i)<<endl;
        }

    }*/
    return * p_cd;
}

pointset Clusterer::toDisplayVals(const dataset &ds){
    pointset * ps = new pointset();
    for(int i = 0; i<ds.size();++i){
       vector<float> vf;
        for(int j = 0; j<ds[i].size();++j){
            vf.push_back((float)ds[i][j]);
        }
        ps->push_back(vf);
    }
     return* ps;
}
dataset Clusterer::getSelfDataset(){
    return self_dataset;
}
