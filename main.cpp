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

vector<cluster> create_centroids(data_feed){
    

    return ;
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

    vector<cluster> clusters=create_centroids(data_set,num_clusters);
    vector<int> clusters=create_centroids();
    return 0;
}





