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

vector<cluster> create_random_centroids(data_point<double> *dat,int k,int length){
    int flag=0;
    vector<cluster> clusters1;
    std::random_device rd; // assume unsigned int is 32 bits
    std::mt19937_64 generator(rd()); // seeded with 256 bits of entropy from random_device
    std::uniform_int_distribution<int>   uint_dist(0,length-1);
    for(int i=0 ; i < k ;i++){
        cluster temp1=cluster(dat[uint_dist(generator)]);
        for (int j=0;j<clusters1.size();j++){
            if(clusters1[j].get_centroid().name==temp1.get_centroid().name){
                i--;
                flag=1;
                break;
            }
        }
        if (flag==0)
            clusters1.push_back(temp1);
        else
            flag=0;
    }
    return clusters1;
}

double euclidean_dist(vector<double> p1,vector<double> p2) {
    double sum = 0.0;
    for (int i=0 ; i<p1.size();i++){
        sum+=(p1[i]-p2[i])*(p1[i]-p2[i]);
    }
    sum = sqrt(sum);
    return sum;
}

vector<cluster> create_kmeans_centroids(data_point<double> *dat,int k,int length){
    double dist_max,dist;
    data_point<double> temp_cent;
    vector<cluster> clusters1;
    std::random_device rd; // assume unsigned int is 32 bits
    std::mt19937_64 generator(rd()); // seeded with 256 bits of entropy from random_device
    std::uniform_int_distribution<int>   uint_dist(0,length-1);
    cluster temp1=cluster(dat[uint_dist(generator)]);
    clusters1.push_back(temp1);
    temp_cent = temp1.get_centroid();
    while (--k>0){
        dist_max=0.0;
        for(int i=0 ; i < length ;i++){
            for(int j=0;j<clusters1.size();j++){
                if ((dist=euclidean_dist(dat[i].point,clusters1[j].get_centroid().point))>dist_max){
                    dist_max=dist;
                    temp_cent=dat[i];
                }
            }
        }
        clusters1.push_back(temp_cent);
    }
    return clusters1;
}



int main(int argc, char** argv) {
    int c,num_lines=0,dim=0;
    int num_clusters = 5;
    int num_hfunc = 4;
    int num_htables = 5;
    string input="", conf1="", output1="", metric1="";
    int i=0;
    /* Reading Arguments from command line */
    while ((c = getopt(argc, argv, "i:c:o:d:")) != -1) {
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
    cout << "dimension: " << dim <<endl;
    cout << "lines: " << num_lines << endl;

    data_point<double> data_set[num_lines];
    feed_data_set(input,data_set,dim);

    vector<cluster> clusters=create_random_centroids(data_set,num_clusters,num_lines);

    for(int z=0;z<clusters.size();z++){
        cout << "This is the cluster center: " << z <<  endl;
        clusters[z].print_centroid();
    }
    return 0;
}





