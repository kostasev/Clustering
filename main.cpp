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

void assign_to_clusters(data_point<double> *dat,vector<cluster> &clusters,int num_lines){
    double dist_min,dist;
    int cluster;
    for (int i=0;i<num_lines;i++){
        dist_min=100000.0;
        cluster=0;
        for(int j=0;j<clusters.size();j++){
            if ((dist=euclidean_dist(dat[i].point,clusters[j].get_centroid().point))<dist_min){
                dist_min=dist;
                cluster=j;
            }
        }
        clusters[cluster].add_item(dat[i]);
    }
}

double silhouette_cluster(cluster cl,data_point<double> item){
    vector<data_point<double>> items = cl.get_items();
    double sum=0.0;
    for (int i=0 ; i < items.size(); i++ ){
        sum+=euclidean_dist(item.point,items[i].point);
    }
    return sum/items.size();
}

int find_nbcluster(vector<cluster> clusters,int avoid,data_point<double> item){
    int best=0;
    double dist_min=100000.0,dist;
    for (int i=0; i<clusters.size(); i++){
        if(i==avoid) continue;
        if ((dist=euclidean_dist(clusters[i].get_centroid().point,item.point))<dist_min){
            dist_min=dist;
            best=i;
        }
    }
    return best;
}




void silhouette(vector<cluster> clusters){
    int next_best_clust=0;
    double total=0.0,total_sils=0.0;
    double a = 0.0 , b = 0.0 ,max;
    for (int i=0; i < clusters.size() ; i++){
        vector<data_point<double>> items = clusters[i].get_items();
        for (int j=0; j<items.size() ; j++){
            a=silhouette_cluster(clusters[i],items[j]);
            next_best_clust=find_nbcluster(clusters,j,items[j]);
            b=silhouette_cluster(clusters[next_best_clust],items[j]);
            if(a>b)
                max=a;
            else max=b;
            total+=(b-a)/max;
        }
        cout <<"Silhouette of Cluster " << i << " is: " << total/items.size() << endl;
        total_sils+=total/items.size();
        total=0.0;
        items.clear();
    }
    cout <<"Silhouette Total: " << total_sils/clusters.size() << endl;
}

void gen_random(char *s, const int len) {
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

vector<double> calculate_mean_centroid(cluster cl) {
    vector<data_point<double>> cluster_dat = cl.get_items();
    int size = (int) cluster_dat.size();
    int len = 0;
    if(size > 0 )
        len=cluster_dat[0].point.size();
    vector<double> new_cl(204, 0.0);

    if(size > 0 && len == 204){
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < size; j++) {
                new_cl[i] += cluster_dat[j].point[i];
            }
        }

        for (int i = 0; i < 204; i++){
            new_cl[i]/=size;
        }
    }
    return new_cl;
}


int update_clusters(data_point<double> *dat,vector<cluster> &clusters,int num_lines){
    /*vector<cluster> temp;
    for (int i=0;i<clusters.size(); i++){
        temp.push_back(clusters[i]);
    }*/
    clusters[0].print_cluster();
    for (int i=0;i<clusters.size();i++){
        vector<double> new_centrer = calculate_mean_centroid(clusters[i]);
        data_point<double> temp1;
        temp1.name="Mean";
        temp1.point=new_centrer;
        clusters[i].set_centroid(temp1);
        new_centrer.clear();
        temp1.point.clear();
    }
    clusters[0].print_cluster();
    /*for(int i=0;i<clusters.size();i++){
        clusters[i].empty_clitems();
    }
    clusters[0].print_cluster();
    assign_to_clusters(dat,clusters,num_lines);
    clusters[0].print_cluster();
    for(int i=0;i<clusters.size();i++){
        if (clusters[i].check_equal(temp[i]) == 1 )
            return 1;
    }*/
    return 0;
}

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



vector<cluster> create_kmeans_centroids(data_point<double> *dat,int k,int length){
    double dist_max,dist,dist_min;
    data_point<double> temp_cent,temp_cent2;
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
            dist_min=100000.0;
            for(int j=0;j<clusters1.size();j++){
                if ((dist=euclidean_dist(dat[i].point,clusters1[j].get_centroid().point))<dist_min){
                    dist_min=dist;
                    temp_cent=dat[i];
                }
            }
            if (dist_min>dist_max){
                dist_max=dist_min;
                temp_cent2=temp_cent;
            }
        }
        clusters1.emplace_back(temp_cent2);
    }
    return clusters1;
}



int main(int argc, char** argv) {
    int c,num_lines=0,dim=0;
    int num_clusters = 5;
    int num_hfunc = 4;
    int num_htables = 5;
    int exit_rep = 10;
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

    vector<cluster> clusters=create_kmeans_centroids(data_set,num_clusters,num_lines);

    assign_to_clusters(data_set,clusters,num_lines);

    vector<cluster> temp;
    int same=0;
    char rand_name[21];
    for(int r=0;r<100;r++){

        for (int i=0;i<clusters.size(); i++){
            temp.push_back(clusters[i]);
        }

        for (int i=0;i<clusters.size();i++){
            //vector<double> new_centrer = calculate_mean_centroid(clusters[i]);
            vector<double> new_centrer = calculate_pam_centroid(clusters[i]);
            cout << "size new center: " << new_centrer.size() << "rep"<< i<< endl;
            for (int z=0;z <204;z++)
                cout << " " << new_centrer[z];
            cout <<endl <<endl;
            data_point<double> temp1;
            gen_random(rand_name,20);
            temp1.name="Mean";
            temp1.name.append(rand_name);
            temp1.point=new_centrer;
            clusters[i].set_centroid(temp1);
            new_centrer.clear();
            temp1.point.clear();
        }

        for(int r=0;r<clusters.size();r++){
            clusters[r].empty_clitems();
        }

        assign_to_clusters(data_set,clusters,num_lines);

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
        cout << "rep: " << r <<endl;
    }
    silhouette(clusters);
    return 0;
}





