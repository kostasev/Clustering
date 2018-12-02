#include <iostream>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <getopt.h>
#include <cstring>
#include <numeric>
#include <cmath>
#include <chrono>
#include <random>
#include <unistd.h>
#include "utilities.h"
#include "data_point.h"
#include "cluster.h"

using namespace std;

int main(int argc, char** argv) {
    int c,num_lines=0,dim=0;
    int num_clusters = 5;
    int num_hfunc = 4;
    int num_htables = 5;
    int exit_rep = 10;
    string input="", conf1="", output1="", metric1="euclidean";
    int i=0;
    int init=0;   //default init method   : Random
    int assign=0; //default assign method : Lloyds
    int update=0; //default update method : Kmeans
    /* Reading Arguments from command line */
    while ((c = getopt(argc, argv, "i:c:o:d:I:A:U:")) != -1) {
        switch (c) {
            case 'i':
                input = optarg;
                break;
            case 'c':
                conf1 =  optarg;
                break;
            case 'o':
                output1 = optarg;
                break;
            case 'I':
                init = atoi(optarg);
                break;
            case 'A':
                assign = atoi(optarg);
                break;
            case 'U':
                update = atoi(optarg);
                break;
            case 'd':
                metric1 = optarg;
                if ((metric1 != "cosine") && (metric1 != "euclidean")) {
                    cerr << "Invalid function name" << endl;
                }
                break;
            case 'h':
                cout << "\nCluster\n" << endl <<
                     "Mandatory options\n\t-i -c\n\n"
                     "\t-i input file\n"
                     "\t-c conf file\n"
                     "\t-o output file\n"
                     "\t-d metric" << endl;
                return 0;
            case '?':
                cerr << "Unknown option character " << char(optopt) << endl;
                return 1;
            default:
                abort();
        }
    }
    get_cfg(conf1,num_clusters,num_hfunc,num_htables);
    get_data_lengths(input,num_lines,dim);
    data_point<double> data_set[num_lines];
    feed_data_set(input,data_set,dim);
    vector<cluster> clusters;
    if(init == 0)
        clusters=create_random_centroids(data_set,num_clusters,num_lines);
    else
        clusters=create_kmeans_centroids(data_set,num_clusters,num_lines,metric1);
    assign_to_clusters(data_set,clusters,num_lines,metric1);
    vector<cluster> temp;
    int same=0;
    char rand_name[21];
    for(int r=0;r<10;r++){
        for (int i=0;i<clusters.size(); i++){
            temp.push_back(clusters[i]);
        }
        for (int i=0;i<clusters.size();i++){
            vector<double> new_centrer;
            if( update == 0 )
                new_centrer = calculate_mean_centroid(clusters[i]);
            else
                 new_centrer = calculate_pam_centroid(clusters[i],metric1);
            data_point<double> temp1;
            gen_random(rand_name,5);
            temp1.name="Mean_";
            temp1.name.append(rand_name);
            temp1.point=new_centrer;
            clusters[i].set_centroid(temp1);
            new_centrer.clear();
            temp1.point.clear();
        }
        for(int r=0;r<clusters.size();r++){
            clusters[r].empty_clitems();
        }
        assign_to_clusters(data_set,clusters,num_lines,metric1);
        for(int i=0;i<clusters.size();i++){
            if (clusters[i].check_equal(temp[i]) == 1 ){
                same++;
            }
        }
        if (same==clusters.size()){
            cout << "Cluster did not change. Exit rep: "<< r << endl;
            temp.clear();
            break;
        }
        same=0;
        temp.clear();
        cout << "iterration: " << r <<endl;
    }
    silhouette(clusters,metric1);
    return 0;
}