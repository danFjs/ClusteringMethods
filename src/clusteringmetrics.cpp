#include "clusteringmetrics.h"
#include "pyclustering/cluster/gmeans_data.hpp"
#include "pyclustering/cluster/xmeans_data.hpp"

using namespace std;
using namespace pyclustering::clst;


ClusteringMetrics::ClusteringMetrics()
{

}

void ClusteringMetrics::shilouette_score(const pyclustering::dataset & p_data, const cluster_sequence & p_clusters)
{
    silhouette_data result;
    silhouette sh;
    sh.process(p_data,p_clusters,result);
    cout<<"Silhouette score for every point: "<<endl;
    for (int var = 0; var < result.get_score().size(); ++var) {
        double score =result.get_score()[var];
        if(std::isnan(score)){
            score = 0;
            result.get_score()[var] = score;
        }

        cout<<score<<endl;
    }

    cout<<"Silhouette score for clusters : "<<endl;
    for (int c = 0; c < p_clusters.size(); ++c) {
    const pyclustering::clst::cluster &current = p_clusters[c];
    vector<double> scores;
    scores.resize(current.size());
    for (int element = 0; element < current.size(); ++element) {
    const int index = current[element];
    scores[element] = result.get_score()[index];
    }
    double avg = std::reduce(scores.begin(),scores.end())/current.size();
    cout<<avg<<endl;

    }
    double average = std::reduce(result.get_score().begin(),result.get_score().end())/result.get_score().size();
    cout<<"Overall Silhouette score is: "<<endl<<average<<endl;

}

void ClusteringMetrics::elbow_analysis(const pyclustering::dataset &ds, const int &kmin, const int &kmax)
{

            elbow<> elbow_instance =elbow(kmin,kmax,1);
            

            elbow_data result = elbow_data();
            elbow_instance.process(ds,result);

            cout<<"Elbow analysis shows:"<<endl;
            cout<<"Optimal amount of clusters:"<<to_string(result.get_amount())<<endl;
            cout<<"Within cluster errors:"<<endl;
            for (int var = 0; var < result.get_wce().size(); ++var) {
                cout<<"Cluster with "<<var+kmin<<" centers | wce: "<<result.get_wce()[var]<<endl;
            }
}

void ClusteringMetrics::calinski_harabasz_score(const pyclustering::dataset &p_ds, const pyclustering::clst::cluster_data &p_clustered_data)
{
    size_t num_samples = p_ds.size();
    const auto& clusters = p_clustered_data.clusters();
    size_t num_labels = clusters.size();
    if(num_labels<1 || num_labels<1){
        throw runtime_error("ch score bad clustering");
    }
    double intra_disp = 0;
    double extra_disp = 0;
    size_t dim = p_ds[0].size();
    double col_means[dim];
    double cluster_means[num_labels][dim];
    for (size_t x = 0; x < dim; ++x) {
        double col_sum = 0;
        for (size_t i = 0; i < num_labels ; ++i) {
            double cluster_sum = 0;
            for (size_t j = 0; j < clusters[i].size(); ++j) {
                cluster_sum+=p_ds[clusters[i][j]][x]; 
            }
            cluster_means[i][x] = cluster_sum/num_labels; 
            col_sum+=cluster_sum;

        }
        col_means[x] = col_sum/num_samples;  

    }
    for (size_t k = 0; k < num_labels; ++k) {
        cluster c = clusters[k];
        double sum_mean_diff = 0;
        for (size_t index = 0; index < dim; ++index) {
            sum_mean_diff+= std::pow(cluster_means[k][index]-col_means[index],2);
        }
        extra_disp+=c.size()*sum_mean_diff;
        double sum_cl_diff = 0;
        for (size_t x = 0; x < c.size(); ++x) {
            for (size_t y = 0; y < dim; ++y) {
                sum_cl_diff+=std::pow((p_ds[c[x]][y]-cluster_means[k][y]),2);
            }
        }
        intra_disp+= sum_cl_diff;

    }
    cout<<"c-h index:"<<endl;
    if(intra_disp==0){
       cout<<1.0<<endl;
    }else{
        double score;
        if(0<intra_disp * (num_labels - 1.0)){
            score = extra_disp * (num_samples - num_labels)  / (intra_disp * (num_labels - 1.0)); 
        }else{
            score = 1;
        }
        cout<<score<<endl;
    }

}

void ClusteringMetrics::davies_bouldin_score(const pyclustering::dataset &p_ds, const pyclustering::clst::cluster_data &p_clustered_data)
{

    const size_t num_samples = p_ds.size();
    const auto& clusters = p_clustered_data.clusters();
    const size_t num_labels = clusters.size();
    const size_t dim = p_ds[0].size();
    double col_means[dim];

    double intra_dists[num_labels];
    double centroids[num_labels][dim];

    for (size_t x = 0; x < dim; ++x) {
        double col_sum = 0;
        for (size_t i = 0; i < num_labels ; ++i) {
            double cluster_sum = 0;
            for (size_t j = 0; j < clusters[i].size(); ++j) {
                cluster_sum+=p_ds[clusters[i][j]][x];
            }
            centroids[i][x] = cluster_sum/num_labels;
            col_sum+=cluster_sum;

        }
        col_means[x] = col_sum/num_samples;

    }
    bool intranull = true;
    for (size_t label = 0; label < num_labels; ++label) {
        double avg;
        const cluster c = clusters[label];
        double sum_dist = 0;
        for (size_t i = 0; i < c.size(); ++i) {
            double sum_sqrt = 0;
            for (size_t j = 0; j < dim; ++j) {
            sum_sqrt+=std::pow((p_ds[c[i]][j]-centroids[label][j]),2);
            }
            sum_dist+=std::sqrt(sum_sqrt);
        }
        avg = sum_dist/c.size();
        intra_dists[label] = avg;
        if(avg!=0){
            intranull =false;
        }
    }
    bool centroidnull = true;
    double centroid_distances[num_labels][num_labels];
    for (size_t i = 0; i < num_labels; ++i) {
        for (size_t j = 0; j < num_labels; ++j) {
            double sum_sqrt = 0;
            for (size_t m_dim = 0; m_dim < dim; ++m_dim) {
                sum_sqrt += std::pow(centroids[i][dim]-centroids[j][dim],2);
            }
            if(std::sqrt(sum_sqrt)!=0){
                centroidnull=false;
                centroid_distances[i][j] = std::sqrt(sum_sqrt);
                centroid_distances[j][i] = std::sqrt(sum_sqrt);
            }else{
                centroid_distances[i][j] = INFINITY;
                centroid_distances[j][i] = INFINITY;
            }

        }
    }
    double intra_distances[num_labels][num_labels];
    for (size_t i = 0; i < num_labels; ++i) {
        for (size_t j = 0; j < num_labels; ++j) {
            intra_distances[i][j] = intra_dists[i]+intra_dists[j];

        }
    }
   cout<<"d-b index:"<<endl;
    if(centroidnull || intranull){
        cout<<0<<endl;

        return;
    }
    double sum_scores = 0;

    for (size_t i = 0; i < num_labels; ++i) {
        double rowmax = 0;
        for (size_t j = 0; j < num_labels; ++j) {
        if(intra_distances[i][j]/centroid_distances[i][j] > rowmax){
            rowmax = intra_distances[i][j]/centroid_distances[i][j];
        }


        }
        sum_scores+=rowmax;

    }
    double end_score = sum_scores/num_labels;
    cout<<end_score<<endl;





}

void ClusteringMetrics::wce(const kmeans_data &p_clustered_data)
{
    cout<<"wce:"<<endl;
    cout<<p_clustered_data.wce()<<endl;
}
double ClusteringMetrics::entropy(const pyclustering::clst::cluster_data &p_clustered_data)
{
    const auto& clusters = p_clustered_data.clusters();
    const size_t num_clusters = p_clustered_data.clusters().size();
    unsigned clustersize[num_clusters];
    double clusterpercent[num_clusters];
    double numberOfElements = 0;
    double clusterlog[num_clusters];
    for (int i = 0; i < num_clusters; ++i) {
        clustersize[i] = p_clustered_data.clusters()[i].size();
        numberOfElements+=clustersize[i];
    }
    double endSum;
    for (int i = 0; i < num_clusters; ++i) {
        clusterpercent[i] = clustersize[i]/numberOfElements;
        clusterlog[i] = std::log(clustersize[i])-std::log(numberOfElements);
        endSum+=clusterpercent[i]*clusterlog[i];
    }
    cout<<endl;
    return -endSum;

}

vector<vector<size_t> > ClusteringMetrics::contingency_matrix(const pyclustering::clst::cluster_data &p_predicted_clusters, const pyclustering::clst::cluster_data &p_true_clusters)
{
    const size_t pred_size = p_predicted_clusters.clusters().size();
    const size_t true_size = p_true_clusters.clusters().size();

    size_t num_pred_elements = 0;
    size_t num_true_elements = 0;
    for (size_t cl = 0; cl < pred_size; ++cl) {
        num_pred_elements+=p_predicted_clusters.clusters()[cl].size();
    }
    for (size_t cl = 0; cl < true_size; ++cl) {
        num_true_elements+=p_true_clusters.clusters()[cl].size();
    }
    if(num_true_elements!=num_pred_elements){
        cerr<<"Contingency matrix: the given clusters should be the same size, but you gave "<<num_pred_elements<<" with "<<num_true_elements<<endl;
        throw runtime_error("contingency_matrix error"); 
    }


    vector<vector<size_t>> result;
    result.resize(true_size);
    for (size_t row = 0; row < true_size; ++row) {
        result[row].resize(pred_size,0);
    }

    for (size_t pred_clust_index = 0; pred_clust_index < pred_size; ++pred_clust_index) {
        cluster pred_clust = p_predicted_clusters.clusters()[pred_clust_index];
        for (size_t pred_index = 0; pred_index < pred_clust.size(); ++pred_index) {
            size_t predicted_number = pred_clust[pred_index];
            for (size_t true_clust_index = 0; true_clust_index < true_size; ++true_clust_index) {
                cluster true_clust = p_true_clusters.clusters()[true_clust_index];
                for (size_t true_index = 0; true_index < true_clust.size(); ++true_index) {
                    if(predicted_number == true_clust[true_index]){
                    result[true_clust_index][pred_clust_index]++;
                    }
                }
            }
        }
    }
    return result;
}

vector<vector<double> > ClusteringMetrics::pair_contingency(const pyclustering::clst::cluster_data &p_predicted_clusters, const pyclustering::clst::cluster_data &p_true_clusters)
{
     const size_t pred_size = p_predicted_clusters.clusters().size();
    const size_t true_size = p_true_clusters.clusters().size();

    size_t num_pred_elements = 0;
    size_t num_true_elements = 0;
    for (size_t cl = 0; cl < pred_size; ++cl) {
        num_pred_elements+=p_predicted_clusters.clusters()[cl].size();
    }
    for (size_t cl = 0; cl < true_size; ++cl) {
        num_true_elements+=p_true_clusters.clusters()[cl].size();
    }

    if(num_true_elements!=num_pred_elements){
        cerr<<"Contingency matrix: the given clusters should be the same size, but you gave "<<num_pred_elements<<" with "<<num_true_elements<<endl;
        throw runtime_error("pair_contingency error");  
    }
    vector<vector<double>> result;
    result.resize(2);
    for (size_t row = 0; row < 2; ++row) {
        result[row].resize(2);
    }

    const vector<vector<size_t>> contingency=contingency_matrix(p_predicted_clusters,p_true_clusters);
    double row_sum[true_size];
    double col_sum[pred_size];
    double sum_squares = 0 ;

    for (size_t pred_clust_index = 0; pred_clust_index < pred_size; ++pred_clust_index) {
        for (size_t true_clust_index = 0; true_clust_index < true_size; ++true_clust_index) {
            row_sum[true_clust_index]+= contingency[true_clust_index][pred_clust_index];
            sum_squares+=std::pow(contingency[true_clust_index][pred_clust_index],2);
        }
    }

    for (size_t true_clust_index = 0; true_clust_index < true_size; ++true_clust_index) {
        for (size_t pred_clust_index = 0; pred_clust_index < pred_size; ++pred_clust_index) {
            col_sum[true_clust_index] += contingency[true_clust_index][pred_clust_index];
        }
    }

    double scalar_row_sum = 0;
    double scalar_col_sum = 0;

    for (size_t pred_clust_index = 0; pred_clust_index < pred_size; ++pred_clust_index) {
        for (size_t true_clust_index = 0; true_clust_index < true_size; ++true_clust_index) {
            scalar_row_sum += row_sum[pred_clust_index] * contingency[true_clust_index][pred_clust_index];

        }
    }

    for (size_t true_clust_index = 0; true_clust_index < true_size; ++true_clust_index) {
        for (size_t pred_clust_index = 0; pred_clust_index < pred_size; ++pred_clust_index) {
            scalar_col_sum +=col_sum[true_clust_index] * contingency[true_clust_index][pred_clust_index];
        }
    }

    result[1][1]=sum_squares-num_pred_elements;
    result[0][1]=scalar_col_sum-sum_squares;
    result[1][0]=scalar_row_sum-sum_squares;
    result[0][0]= (((std::pow(num_pred_elements,2) - result[0][1]) - result[1][0]) - sum_squares);

    return result;


}

double ClusteringMetrics::mutual_information(const pyclustering::clst::cluster_data &p_predicted_clusters, const pyclustering::clst::cluster_data &p_true_clusters)
{
    double result = 0;
    const size_t pred_size = p_predicted_clusters.clusters().size();
    const size_t true_size = p_true_clusters.clusters().size();

    if(pred_size == 1 || true_size == 1){
        return 0;
    }

    size_t num_pred_elements = 0;
    size_t num_true_elements = 0;
    for (size_t cl = 0; cl < pred_size; ++cl) {
        num_pred_elements+=p_predicted_clusters.clusters()[cl].size();
    }
    for (size_t cl = 0; cl < true_size; ++cl) {
        num_true_elements+=p_true_clusters.clusters()[cl].size();
    }

    if(num_true_elements!=num_pred_elements){
        cerr<<"Contingency matrix: the given clusters should be the same size, but you gave "<<num_pred_elements<<" with "<<num_true_elements<<endl;
        throw runtime_error("Something went wrong");
    }

    vector<vector<size_t>> contingency = contingency_matrix(p_predicted_clusters,p_true_clusters);
    vector<size_t> row_sum; //pi
    vector<size_t> col_sum; //pj
    double row_sum_sum = 0;
    double col_sum_sum = 0;
    vector<size_t> nonzero_x;
    vector<size_t> nonzero_y;
    vector<double> nonzero_val;
    vector<double> nonzero_log_val; //log_contingency_nm
    vector<double> nonzero_val_divsum; // contingency_nm
    for (size_t pred_clust_index = 0; pred_clust_index < pred_size; ++pred_clust_index) {
        for (size_t true_clust_index = 0; true_clust_index < true_size; ++true_clust_index) {
            if(true_clust_index == 0){
                row_sum.push_back(contingency[true_clust_index][pred_clust_index]);
            }else{
                row_sum[pred_clust_index]+= contingency[true_clust_index][pred_clust_index];
            }
            row_sum_sum+=contingency[true_clust_index][pred_clust_index];
            if(contingency[true_clust_index][pred_clust_index]!=0){
                nonzero_x.push_back(true_clust_index);
                nonzero_y.push_back(pred_clust_index);
                nonzero_val.push_back(contingency[true_clust_index][pred_clust_index]);
                nonzero_log_val.push_back(std::log(contingency[true_clust_index][pred_clust_index]));
                nonzero_val_divsum.push_back(static_cast<double>(contingency[true_clust_index][pred_clust_index])/static_cast<double>(num_pred_elements));
            }
        }
    }

    for (size_t true_clust_index = 0; true_clust_index < true_size; ++true_clust_index) {
        for (size_t pred_clust_index = 0; pred_clust_index < pred_size; ++pred_clust_index) {
            if(pred_clust_index == 0){
                col_sum.push_back(contingency[true_clust_index][pred_clust_index]);
            }else{

                col_sum[true_clust_index] += contingency[true_clust_index][pred_clust_index];
            }
            col_sum_sum += contingency[true_clust_index][pred_clust_index];
        }
    }

    vector<double> log_outer;
    const double logsums = std::log(row_sum_sum)+std::log(col_sum_sum);
    for (size_t take = 0; take < nonzero_val.size(); ++take) {
        size_t a = row_sum[nonzero_y[take]];
        size_t b = col_sum[nonzero_x[take]];
        double outer = static_cast<double>(a)*static_cast<double>(b);
        double logouter = std::log(outer);
        log_outer.push_back(-1*logouter+logsums);

    }
    vector<double> mi;
    const double log_contsum = std::log(num_pred_elements);
    for (size_t i = 0; i < log_outer.size(); ++i) {
        double temp_mi = nonzero_val_divsum[i] * ( nonzero_log_val[i] - log_contsum ) + nonzero_val_divsum[i]*log_outer[i];
        mi.push_back(temp_mi);
    }
    for (size_t mi_i = 0; mi_i < mi.size(); ++mi_i) {
        result+=mi[mi_i];
    }
    return result;
}

double ClusteringMetrics::homogeneity_score(const pyclustering::clst::cluster_data &p_predicted_clusters, const pyclustering::clst::cluster_data &p_true_clusters)
{
    double entropy_true = entropy(p_true_clusters);
    double mutual_info = mutual_information(p_predicted_clusters,p_true_clusters);
    double homogenity;
    if(entropy_true>0){
        homogenity = mutual_info/entropy_true;
    }
    else{
        homogenity = 1.0;
    }

    return homogenity;
}

double ClusteringMetrics::completeness_score(const pyclustering::clst::cluster_data &p_predicted_clusters, const pyclustering::clst::cluster_data &p_true_clusters)
{
    double entropy_pred = entropy(p_predicted_clusters);
    double mutual_info = mutual_information(p_predicted_clusters,p_true_clusters);
    double completeness;
    if(completeness>0){
        if(entropy_pred>0){

            completeness = mutual_info/entropy_pred;  
        }else{
            completeness = mutual_info/1;
        }

    }
    else{
        completeness = 1.0;
    }
    return completeness;
}

double ClusteringMetrics::v_measure_score(const pyclustering::clst::cluster_data &p_predicted_clusters, const pyclustering::clst::cluster_data &p_true_clusters, const double &beta)
{

    double homogeneity_v = homogeneity_score(p_predicted_clusters,p_true_clusters);
    double completeness_v = completeness_score(p_predicted_clusters,p_true_clusters);
    double v_measure;
    if(homogeneity_v +completeness_v == 0){
        return 0;
    }else{
        try {
            v_measure= ((1 + beta)* homogeneity_v* completeness_v/(beta * homogeneity_v + completeness_v));
        } catch (...) {
            v_measure= ((1 + beta)* homogeneity_v* completeness_v/1);
        }
  
    }
    return v_measure;
}

double ClusteringMetrics::rand_index(const pyclustering::clst::cluster_data &p_predicted_clusters, const pyclustering::clst::cluster_data &p_true_clusters)
{
    vector<vector<double>> contingency  = pair_contingency(p_predicted_clusters,p_true_clusters);
    double contingency_diag_sum =0;
    double contingency_sum = 0;
    for (size_t i = 0; i < contingency.size(); ++i) {
        contingency_diag_sum+=contingency[i][i];
        for (size_t j = 0; j < contingency[i].size(); ++j) {
          contingency_sum += contingency[i][j];
        }
    }

    if(contingency_sum == 0 || contingency_sum == contingency_diag_sum){
        return 1;
    }
    return contingency_diag_sum/contingency_sum;
}

double ClusteringMetrics::adjusted_rand_index(const pyclustering::clst::cluster_data &p_predicted_clusters, const pyclustering::clst::cluster_data &p_true_clusters)
{
    vector<vector<double>> contingency  = pair_contingency(p_predicted_clusters,p_true_clusters);
    double tp = contingency[0][0];
    double tn= contingency[0][1];
    double fn= contingency[1][0];
    double fp= contingency[1][1];
    if(fn == 0 || fp == 0){
        return 1.0;
    }
    try {

        return 2.0 * (tp * tn - fn * fp) / ((tp + fn) * (fn + tn) + (tp + fp) * (fp + tn));  
    } catch (error_t) {
        return 2.0 * (tp * tn - fn * fp) / 1;

    }

}

double ClusteringMetrics::fowlkes_mallows_score(const pyclustering::clst::cluster_data &p_predicted_clusters, const pyclustering::clst::cluster_data &p_true_clusters)
{
    double result = 0;
    const size_t pred_size = p_predicted_clusters.clusters().size();
    const size_t true_size = p_true_clusters.clusters().size();

    if(pred_size == 1 || true_size == 1){
        return 0;
    }

    size_t num_pred_elements = 0;
    size_t num_true_elements = 0;
    for (size_t cl = 0; cl < pred_size; ++cl) {
        num_pred_elements+=p_predicted_clusters.clusters()[cl].size();
    }
    for (size_t cl = 0; cl < true_size; ++cl) {
        num_true_elements+=p_true_clusters.clusters()[cl].size();
    }

    if(num_true_elements!=num_pred_elements){
        cerr<<"Contingency matrix: the given clusters should be the same size, but you gave "<<num_pred_elements<<" with "<<num_true_elements<<endl;
        throw runtime_error("Something went wrong");
    }
    double score = 0.0;
    vector<vector<size_t>> c = contingency_matrix(p_predicted_clusters,p_true_clusters);
    double tk = 0;
    for (size_t i = 0; i < c.size(); ++i) {
        for (size_t j = 0; j < c[i].size(); ++j) {
            tk+= c[i][j]*c[i][j];
        }
    }
    tk-=num_pred_elements;
    vector<size_t> c_sum_ax0 ;
    for (size_t j = 0; j < c[0].size(); ++j) {
        double col = 0;
        for (size_t i = 0; i < c.size(); ++i) {
            col+=c[i][j];
        }
        if(col!=0){
            c_sum_ax0.push_back(col*col);
        }
    }

    vector<size_t> c_sum_ax1 ;

    for (size_t i = 0; i < c.size(); ++i) {
        double row =0;
        for (size_t j = 0; j < c[i].size(); ++j) {
            row+= c[i][j];
        }
        if(row!=0){
            c_sum_ax1.push_back(row*row);
        }

    }

    size_t pk = 0;
    for (size_t i = 0; i < c_sum_ax0.size(); ++i) {
        pk+=c_sum_ax0[i];
    }
    pk-=num_pred_elements;
    size_t qk = 0;

    for (size_t i = 0; i < c_sum_ax1.size(); ++i) {
        qk+=c_sum_ax1[i];
    }
    qk -=num_pred_elements;


    if(tk!=0){
        return std::sqrt((tk / pk)) * std::sqrt((tk / qk));

    }


    return score;
}

double ClusteringMetrics::normalized_mutual_information_score(const pyclustering::dataset &ds, const stringvec clusternames)
{
   /*
 labels_true, labels_pred = check_clusterings(labels_true, labels_pred)
    classes = np.unique(labels_true)
    clusters = np.unique(labels_pred)

    # Special limit cases: no clustering since the data is not split.
    # It corresponds to both labellings having zero entropy.
    # This is a perfect match hence return 1.0.
    if (
        classes.shape[0] == clusters.shape[0] == 1
        or classes.shape[0] == clusters.shape[0] == 0
    ):
        return 1.0

    contingency = contingency_matrix(labels_true, labels_pred, sparse=True)
    contingency = contingency.astype(np.float64, copy=False)
    # Calculate the MI for the two clusterings
    mi = mutual_info_score(labels_true, labels_pred, contingency=contingency)

    # At this point mi = 0 can't be a perfect match (the special case of a single
    # cluster has been dealt with before). Hence, if mi = 0, the nmi must be 0 whatever
    # the normalization.
    if mi == 0:
        return 0.0

    # Calculate entropy for each labeling
    h_true, h_pred = entropy(labels_true), entropy(labels_pred)

    normalizer = _generalized_average(h_true, h_pred, average_method)
    return mi / normalizer


*/
}
