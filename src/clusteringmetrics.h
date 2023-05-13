#ifndef CLUSTERINGMETRICS_H
#define CLUSTERINGMETRICS_H
#include <src/custom_definitions.h>
#include <pyclustering/cluster/elbow.hpp>
#include <pyclustering/cluster/elbow_data.hpp>
#include <pyclustering/cluster/silhouette.hpp>
#include <pyclustering/cluster/silhouette_data.hpp>
#include <iostream>
class ClusteringMetrics
{
public:
    ClusteringMetrics();

    void analyze();
    //unsupervised tests
    void shilouette_score(const pyclustering::dataset &p_data, const pyclustering::clst::cluster_sequence &p_clusters);
    void elbow_analysis(const pyclustering::dataset &ds, const int & kmin , const int &kmax);
    void calinski_harabasz_score(const pyclustering::dataset &p_ds, const pyclustering::clst::cluster_data & p_clustered_data);
    void davies_bouldin_score(const pyclustering::dataset &p_ds, const pyclustering::clst::cluster_data &p_clustered_data);
    void wce(const pyclustering::clst::kmeans_data &p_clustered_data);
    double entropy(const pyclustering::clst::cluster_data & p_clustered_data);
    //supervised tests
    vector<vector<double>> pair_contingency(const pyclustering::clst::cluster_data & p_predicted_clusters , const pyclustering::clst::cluster_data & p_true_clusters );
    double mutual_information(const pyclustering::clst::cluster_data & p_predicted_clusters , const pyclustering::clst::cluster_data & p_true_clusters);
    vector<vector<size_t>> contingency_matrix(const pyclustering::clst::cluster_data & p_predicted_clusters , const pyclustering::clst::cluster_data & p_true_clusters );
    double homogeneity_score(const pyclustering::clst::cluster_data &p_predicted_clusters, const pyclustering::clst::cluster_data & p_true_clusters);
    double completeness_score(const pyclustering::clst::cluster_data &p_predicted_clusters, const pyclustering::clst::cluster_data &p_true_clusters);
    double v_measure_score(const pyclustering::clst::cluster_data & p_predicted_clusters , const pyclustering::clst::cluster_data & p_true_clusters, const double &beta);
    double rand_index(const pyclustering::clst::cluster_data & p_predicted_clusters , const pyclustering::clst::cluster_data & p_true_clusters);
    double adjusted_rand_index(const pyclustering::clst::cluster_data & p_predicted_clusters , const pyclustering::clst::cluster_data & p_true_clusters);
    double fowlkes_mallows_score(const pyclustering::clst::cluster_data & p_predicted_clusters , const pyclustering::clst::cluster_data & p_true_clusters);

    stringset get_classification(pyclustering::clst::cluster_data predicted,pyclustering::clst::cluster_data ground_truth);
};

#endif 
