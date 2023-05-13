#ifndef CLUSTERER_H
#define CLUSTERER_H
#pragma once

#include "custom_definitions.h"
#include <pyclustering/cluster/gmeans.hpp>
#include <pyclustering/cluster/gmeans_data.hpp>
#include <pyclustering/cluster/xmeans.hpp>
#include <pyclustering/cluster/xmeans_data.hpp>
#include <pyclustering/cluster/kmeans.hpp>
#include <pyclustering/cluster/kmeans_data.hpp>
#include <pyclustering/cluster/random_center_initializer.hpp>



#include <iostream>
using namespace pyclustering;
using namespace clst;
class Clusterer
{
public:
/*
    @brief    Constructor of clustering algorithm where algorithm parameters for processing are
               specified.

    @param[in] p_k_initial: initial amount of centers.
    @param[in] p_tolerance: stop condition in following way: when maximum value of distance change of
                cluster centers is less than tolerance then algorithm stops processing.
    @param[in] p_repeat: how many times K-Means should be run to improve parameters (by default is 3),
                with larger `repeat` values suggesting higher probability of finding global optimum.
    @param[in] p_kmax: maximum amount of clusters that might be allocated. The argument is considered as a stop
                condition. When the maximum amount is reached then algorithm stops processing. By default the maximum
                amount of clusters is not restricted (`k_max` is `IGNORE_KMAX`).
    @param[in] p_random_state: seed for random state (by default is `RANDOM_STATE_CURRENT_TIME`, current system time is used).
    */
    Clusterer(const dataset &data);
    gmeans_data run_gmeans(const size_t& p_repeat=pyclustering::clst::gmeans::DEFAULT_REPEAT,
                           const long long &p_kmax=pyclustering::clst::gmeans::IGNORE_KMAX,
                            const size_t &p_k_initial = 1,
                            const double &p_tolerance= pyclustering::clst::gmeans::DEFAULT_TOLERANCE ,
                            const long long& p_random_state =RANDOM_STATE_CURRENT_TIME);

    xmeans_data run_xmeans(const dataset & p_initial_centers,
                           const std::size_t p_kmax ,
                           const size_t p_repeat = 1,
                           const double p_tolerance = pyclustering::clst::xmeans::DEFAULT_TOLERANCE,
                           const splitting_type p_criterion=pyclustering::clst::xmeans::DEFAULT_SPLITTING_TYPE,

                           const long long p_random_state=RANDOM_STATE_CURRENT_TIME,
                           const distance_metric<point> & p_metric=distance_metric_factory<point>::euclidean_square());

    kmeans_data run_kmeans(const dataset & p_initial_centers,
                           const double p_tolerance = pyclustering::clst::kmeans::DEFAULT_TOLERANCE,
                           const std::size_t p_itermax =pyclustering::clst::kmeans::DEFAULT_ITERMAX,
                           const distance_metric<point> & p_metric=distance_metric_factory<point>::euclidean_square());



    dataset initialize_random_centers(const int &num = 1,const long long random_state=RANDOM_STATE_CURRENT_TIME);
    pointsetset toDisplayVals(const gmeans_data &);
    pointsetset toDisplayVals(const xmeans_data &);
    pyclustering::clst::cluster_data usePredefinedClusters(const stringvec & classes);
    pyclustering::dataset getSelfDataset();
    stringset toStringSet(gmeans_data);
    stringset toStringSet(xmeans_data);
    pointset toDisplayVals(const dataset &ds);
    pointsetset toDisplayVals(const cluster_data &);
private:
    pyclustering::dataset self_dataset;

};

#endif 
