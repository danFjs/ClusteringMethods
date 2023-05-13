#include <QCoreApplication>
#include <iostream>
#include <string>
#include <QtCharts>
#include "chartview.h"
#include "filehandler.h"
#include "clusterer.h"
#include "clusteringmetrics.h"

int analyze_test_data(int argc, char *argv[]){
    QApplication a(argc, argv);
    FileHandler * fh = new FileHandler("/home/d/Downloads/klaszter.txt",true);

    fh->cleanUpColNames();
    fh->dropCols({"num"});
    fh->useClusters("kat");

    pyclustering::dataset ds = fh->toDataset(fh->getContents());
    ClusteringMetrics cms;
    ChartView ch;
    Clusterer clr = Clusterer(ds);
    gmeans_data gd = clr.run_gmeans(50,31);

    xmeans_data  xd = clr.run_xmeans(clr.initialize_random_centers(),31,50);
 
    auto clusses = gd;
    auto reference = clr.usePredefinedClusters(fh->getClusters());

    cout<<"GMEANS:"<<endl;
    cms.shilouette_score(ds,gd.clusters());
    cms.elbow_analysis(ds,1,31);
    cms.calinski_harabasz_score(ds,gd);
    cms.davies_bouldin_score(ds,gd);
    cout<<"wce:"<<endl;
    cout<<gd.wce()<<endl;
    cout<< "Entropy: "<<cms.entropy(gd)<<endl;
    cout<<gd.centers().size()<<" számú klasztert talált " <<endl;
    cout<<"XMEANS:"<<endl;
    cms.shilouette_score(ds,xd.clusters());
    cms.elbow_analysis(ds,1,31);
    cms.calinski_harabasz_score(ds,xd);
    cms.davies_bouldin_score(ds,xd);
    cout<<"wce:"<<endl;
    cout<<xd.wce()<<endl;
    cout<< "Entropy: "<<cms.entropy(xd)<<endl;
    cout<<xd.centers().size()<<" számú klasztert talált " <<endl;


    cout<<"XMEANS:"<<endl;
    cout<<"MI:"<<cms.mutual_information(xd,reference)<<endl;
    cout<<"H:"<<cms.homogeneity_score(xd,reference)<<endl;
    cout<<"C:"<<cms.completeness_score(xd,reference)<<endl;
    cout<<"V:"<<cms.v_measure_score(xd,reference,1.0)<<endl;
    cout<<"RI:"<<cms.rand_index(xd,reference)<<endl;
    cout<<"ARI:"<<cms.adjusted_rand_index(xd,reference)<<endl;
    cout<<"FM:"<<cms.fowlkes_mallows_score(xd,reference)<<endl;


    cout<<"GMEANS:"<<endl;
    cout<<"MI:"<<cms.mutual_information(gd,reference)<<endl;
    cout<<"H:"<<cms.homogeneity_score(gd,reference)<<endl;
    cout<<"C:"<<cms.completeness_score(gd,reference)<<endl;
    cout<<"V:"<<cms.v_measure_score(gd,reference,1.0)<<endl;
    cout<<"RI:"<<cms.rand_index(gd,reference)<<endl;
    cout<<"ARI:"<<cms.adjusted_rand_index(gd,reference)<<endl;
    cout<<"FM:"<<cms.fowlkes_mallows_score(gd,reference)<<endl;
    pointsetset pss = clr.toDisplayVals(gd);
   ch.addToChart(clr.toDisplayVals(ds));
   for(int i=0; i<pss.size();++i){
      ch.repaint(pss[i],(255-11*i,255-11*i,255-11*i));
   }
    ch.setMouseTracking(true);
    ch.show();
    return a.exec();
}
int analyze_bio_data(int argc, char *argv[]){
    QApplication a(argc, argv);
    FileHandler * fh = new FileHandler("/home/d/Downloads/Data/dataset_114.csv","/home/d/Downloads/Data/ALL_CLASS_NAME.csv",false);

    fh->cleanUpColNames();
    fh->dropCols({"ObjectID"});
    fh->dropCols({"FileID"});
    pyclustering::dataset ds = fh->toDataset(fh->getContents());
    ClusteringMetrics cms;
    ChartView ch;
    Clusterer clr = Clusterer(ds);
    gmeans_data gd = clr.run_gmeans(50,31);

    xmeans_data  xd = clr.run_xmeans(clr.initialize_random_centers(),31,50);

    cout<<"GMEANS:"<<endl;
    cms.shilouette_score(ds,gd.clusters());
    cms.elbow_analysis(ds,1,31);
    cms.calinski_harabasz_score(ds,gd);
    cms.davies_bouldin_score(ds,gd);
    cout<<"wce:"<<endl;
    cout<<gd.wce()<<endl;
    cout<< "Entropy: "<<cms.entropy(gd)<<endl;
    cout<<gd.centers().size()<<" számú klasztert talált " <<endl;
    cout<<"XMEANS:"<<endl;
    cms.shilouette_score(ds,xd.clusters());
    cms.elbow_analysis(ds,1,31);
    cms.calinski_harabasz_score(ds,xd);
    cms.davies_bouldin_score(ds,xd);
    cout<<"wce:"<<endl;
    cout<<xd.wce()<<endl;
    cout<< "Entropy: "<<cms.entropy(xd)<<endl;
    cout<<xd.centers().size()<<" számú klasztert talált " <<endl;

    cout<<"GMEANS:"<<endl;
    cout<<"MI:"<<cms.mutual_information(xd,gd)<<endl;
    cout<<"H:"<<cms.homogeneity_score(xd,gd)<<endl;
    cout<<"C:"<<cms.completeness_score(xd,gd)<<endl;
    cout<<"V:"<<cms.v_measure_score(xd,gd,1.0)<<endl;
    cout<<"RI:"<<cms.rand_index(xd,gd)<<endl;
    cout<<"ARI:"<<cms.adjusted_rand_index(xd,gd)<<endl;
    cout<<"FM:"<<cms.fowlkes_mallows_score(xd,gd)<<endl;


    cout<<"XMEANS:"<<endl;
    cout<<"MI:"<<cms.mutual_information(gd,xd)<<endl;
    cout<<"H:"<<cms.homogeneity_score(gd,xd)<<endl;
    cout<<"C:"<<cms.completeness_score(gd,xd)<<endl;
    cout<<"V:"<<cms.v_measure_score(gd,xd,1.0)<<endl;
    cout<<"RI:"<<cms.rand_index(gd,xd)<<endl;
    cout<<"ARI:"<<cms.adjusted_rand_index(gd,xd)<<endl;
    cout<<"FM:"<<cms.fowlkes_mallows_score(gd,xd)<<endl;
    return a.exec();
}

int main(int argc, char *argv[])
{

    return analyze_bio_data(argc,argv);




}
