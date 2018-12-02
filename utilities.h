//
// Created by kosti on 11/20/2018.
//

#ifndef PROJECT2_UTILITIES_H
#define PROJECT2_UTILITIES_H

#include <fstream>
#include <iostream>
#include <string>
#include "data_point.h"
#include "cluster.h"
#include <cstring>
#include <cmath>
#include <chrono>
#include <random>
#include <unistd.h>

using namespace std;

int num_columns(std::string line) ;
void get_cfg(string inputf, int &clusters, int &hfunc, int &htables) ;
void get_data_lengths(string input,int& lines, int& d) ;
void feed_data_set(string input, data_point<double> *pPoint,int d) ;
double euclidean_dist(vector<double> p1,vector<double> p2) ;
int clusters_equal(cluster x, cluster y);
double cosine_similarity(vector<double> p1,vector<double> p2);
void assign_to_clusters(data_point<double> *dat,vector<cluster> &clusters,int num_lines,string metric);
double silhouette_cluster(cluster cl,data_point<double> item,string metric);
int find_nbcluster(vector<cluster> clusters,int avoid,data_point<double> item,string metric);
void silhouette(vector<cluster> clusters,string metric);
void gen_random(char *s, const int len);
vector<double> calculate_mean_centroid(cluster cl) ;
double obj_func(vector<data_point<double>> items,vector<double> point,string metric);
vector<double> calculate_pam_centroid(cluster cl,string metric);
int update_clusters(data_point<double> *dat,vector<cluster> &clusters,int num_lines);
vector<cluster> create_random_centroids(data_point<double> *dat,int k,int length);
vector<cluster> create_kmeans_centroids(data_point<double> *dat,int k,int length,string metric);


#endif //PROJECT2_UTILITIES_H
