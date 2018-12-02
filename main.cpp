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
#include "Hash_table.h"
#include "constants.h"

using namespace std;

void random_vector(vector<int> &r,int k ){
    std::mt19937 generator;
    generator.seed(std::default_random_engine()());
    std::uniform_int_distribution<int>   int_dist(-99,99);
    for(int i=0; i<k ; i++){
        r.push_back(int_dist(generator));
    }
}

int create_tables(vector<Hash_table> &tables,string metric,int num_lines,int dim){
    int table_size;
    if (metric=="euclidean")
        table_size = num_lines/const_lsh::table_size;
    else
        table_size = (int) pow(2.0,const_lsh::k);

    for (int i=0; i<const_lsh::L ; i++){
        tables.push_back(Hash_table(table_size, dim, const_lsh::k, metric));
    }
    return table_size;
}


void feed_tables(vector<Hash_table> &tables,data_point<double> *data_set,int table_size,int num_lines,vector<int> r){
    for (int j=0;j<tables.size();j++) {
        for (int i = 0; i < num_lines; i++) {
            tables[j].add_item(data_set[i],table_size,r);
        }
    }
}

int query_htables(vector<Hash_table> &tables,vector<cluster> clusters,data_point<double> *data_set2,int num_lines,int table_sz,vector<int>r) {
    map<string, value_point<double>> bucks;
    int ii=0;
    Key query_key;
    data_point<double> temp;
    for(int k=0;k<clusters.size();k++){
        for (int i=0;i<tables.size();i++){
            temp.point=clusters[k].get_centroid().point;
            query_key=tables[i].query_item(temp,table_sz,r);
            tables[i].get_bucket(temp,query_key, bucks,r);
        }
    }
    for (auto  it = bucks.begin(); it != bucks.end(); it++ ){
        data_set2[ii].name=it->second.p->name;
        data_set2[ii].point=it->second.p->point;
        ii++;
    }
    return bucks.size();
}

int main(int argc, char** argv) {
    int c,num_lines=0,dim=0,table_size,num_lines2;
    int num_clusters = 5,num_cl;
    int num_hfunc = 4;
    int num_htables = 5;
    int exit_rep = 25;
    string input="", conf1="", output1="", metric1="euclidean";
    int i=0;
    int init=0;   //default init method   : Random
    int assign=0; //default assign method : Lloyds
    int update=0; //default update method : Kmeans
    /* Reading Arguments from command line */
    while ((c = getopt(argc, argv, "i:c:o:d:I:A:U:k:")) != -1) {
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
            case 'k':
                num_cl = atoi(optarg);
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
    num_clusters=num_cl;
    get_data_lengths(input,num_lines,dim);
    data_point<double> data_set[num_lines],data_set2[num_lines];
    feed_data_set(input,data_set,dim,num_lines);
    vector<cluster> clusters;
    vector<int> r;
    vector <Hash_table> tables ;
    auto start = chrono::steady_clock::now();
    /*Initialization*/
    if(init == 0)   //Random
        clusters=create_random_centroids(data_set,num_clusters,num_lines);
    else            //Kmeans
        clusters=create_kmeans_centroids(data_set,num_clusters,num_lines,metric1);

    if(assign==0)   //Lloyds
        assign_to_clusters(data_set,clusters,num_lines,metric1);
    else if (assign==1){ //LSH
        random_vector(r,const_lsh::k);
        table_size=create_tables(tables,metric1,num_lines,dim);
        feed_tables(tables,data_set,table_size,num_lines,r);
        num_lines2=query_htables(tables,clusters,data_set2,num_lines,table_size,r);
        assign_to_clusters(data_set2,clusters,num_lines2,metric1);
    }
    vector<cluster> temp;
    int same=0;
    char rand_name[21];
    for(int rr=0;rr<exit_rep;rr++){
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
        if(assign==0)
            assign_to_clusters(data_set,clusters,num_lines,metric1);
        else if (assign==1){ //LSH
            //num_lines2=query_htables(tables,clusters,data_set2,num_lines,table_size,r);
            assign_to_clusters(data_set2,clusters,num_lines2,metric1);
        }
        for(int i=0;i<clusters.size();i++){
            if (clusters[i].check_equal(temp[i]) == 1 ){
                same++;
            }
        }
        if (same==clusters.size()){
            cout << "Cluster did not change. Exit rep: "<< rr << endl;
            temp.clear();
            break;
        }
        same=0;
        temp.clear();
        cout << "iterration: " << rr <<endl;
    }
    auto end = chrono::steady_clock::now();
    chrono::duration<double> diff = end-start;
    cout << "Agorithm: " << "I: "<< init << " A: " << assign << " U: " << update << endl;
    cout << "Metric: " << metric1 <<endl;
    for (int i=0; i <clusters.size();i++){
        cout << "Cluster-" << i <<endl;
        clusters[i].print_cluster();
    }
    silhouette(clusters,metric1);
    cout << "Execution time: " << diff.count() << " seconds"<< endl;
    clusters.clear();
    return 0;
}