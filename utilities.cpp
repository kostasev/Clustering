//
// Created by kosti on 11/20/2018.
//
#include "utilities.h"

int num_columns(string line) {
    int words=0;
    char c;
    for(int i=0;i<line.size(); i++){
        if (line[i] == ','){
            words++;
        }
    }
    words++;
    return words;
}

bool vectors_eq(std::vector<double> v1, std::vector<double> v2){
    for (int i = 0 ; i<v1.size() ; i++){
        if(v1[i]!=v2[i]){
            return false;
        }
    }
    return true;
}


void get_cfg(string inputf, int &clusters, int &hfunc, int &htables) {
    ifstream file;
    file.open(inputf);
    if (!file.is_open()){
        cerr << "Failed to open cluster.conf file! " << endl;
        exit(0) ;
    }
    string word;
    while (file >> word)
    {
        if (word == "number_of_clusters:") {
            file >> word;
            clusters=stoi(word);
        } else if (word == "number_of_hash_functions:") {
            file >> word;
            hfunc=stoi(word);
        } else if (word == "number_of_hash_tables:") {
            file >> word;
            htables=stoi(word);
        }

    }
    file.close();
}

double euclidean_dist(vector<double> p1,vector<double> p2) {
    double sum = 0.0;
    for (int i=0 ; i<p1.size();i++){
        sum+=(p1[i]-p2[i])*(p1[i]-p2[i]);
    }
    sum = sqrt(sum);
    return sum;
}

double cosine_similarity(vector<double> p1,vector<double> p2)
{
    double dot = 0.0, denom_a = 0.0, denom_b = 0.0 ;
    for(unsigned int i = 0u; i < p1.size(); i++) {
        dot += p1[i] * p2[i] ;
        denom_a += p1[i] * p1[i] ;
        denom_b += p2[i] * p2[i] ;
    }
    return dot / (sqrt(denom_a) * sqrt(denom_b)) ;
}


int clusters_equal(cluster x, cluster y){
    //if(x.get_items().size()!=y.get_items().size()) return 1;
    return x.check_equal(y);
}

void get_data_lengths(string input,int& lines, int& d) {
    ifstream inputfd;
    string line;
    inputfd.open (input);
    if (inputfd.is_open()){
        getline(inputfd,line);
        d = num_columns(line);
        lines++;
        while ( getline(inputfd,line) ){
            lines++;
        }
        inputfd.close();
    }else{
        cerr << "Unable to open file: " << input << endl;
    }
    inputfd.close();
}
void feed_data_set(string input, data_point<double> *pPoint,int d,int num_lines) {
    char cc[1024] ;
    double dd;
    string name;
    string line;
    ifstream inputfd;
    inputfd.open (input);
    inputfd.exceptions(std::ifstream::failbit|std::ifstream::badbit);
    int i=0,j,z=0;
    cout.precision(15);
    while(z<num_lines){
        for( int ii=0; ii< d-1 ;ii++){
            getline(inputfd,line,',');
            dd=stod(line);
            pPoint[z].point.push_back(dd);
        }
        getline(inputfd,line);
        dd=stod(line);
        pPoint[z].point.push_back(dd);
        pPoint[z].name="item_"+to_string(z+1);
        z++;
    }
    inputfd.close();
}

void assign_to_clusters(data_point<double> *dat,vector<cluster> &clusters,int num_lines,string metric){
    double dist_min,dist;
    int cluster;
    for (int i=0;i<num_lines;i++){
        dist_min=100000.0;
        cluster=0;
        for(int j=0;j<clusters.size();j++){
            if (metric == "euclidean")
                dist=euclidean_dist(dat[i].point,clusters[j].get_centroid().point);
            else
                dist=cosine_similarity(dat[i].point,clusters[j].get_centroid().point);
            if (dist<dist_min){
                dist_min=dist;
                cluster=j;
            }
        }
        clusters[cluster].add_item(dat[i]);
    }
}

double silhouette_cluster(cluster cl,data_point<double> item,string metric){
    vector<data_point<double>> items = cl.get_items();
    double sum=0.0;
    for (int i=0 ; i < items.size(); i++ ){
        if (metric == "euclidean")
            sum+=euclidean_dist(item.point,items[i].point);
        else
            sum+=cosine_similarity(item.point,items[i].point);
    }
    return sum/items.size();
}

int find_nbcluster(vector<cluster> clusters,int avoid,data_point<double> item,string metric){
    int best=0;
    double dist_min=100000.0,dist;
    for (int i=0; i<clusters.size(); i++){
        if(i==avoid) continue;
        //if (clusters[i].get_items().size()==0) continue;
        //if (item.point.size()==0) return 0;
        if (metric == "euclidean")
            dist==euclidean_dist(clusters[i].get_centroid().point,item.point);
        else
            dist=cosine_similarity(clusters[i].get_centroid().point,item.point);
        if (dist<dist_min){
            dist_min=dist;
            best=i;
        }
    }
    return best;
}

void silhouette(vector<cluster> clusters,string metric){
    int next_best_clust=0;
    double total=0.0,total_sils=0.0;
    double a = 0.0 , b = 0.0 ,max;
    for (int i=0; i < clusters.size() ; i++){
        vector<data_point<double>> items = clusters[i].get_items();
        if (items.size()==0) continue;
        for (int j=0; j<items.size() ; j++){
            a=silhouette_cluster(clusters[i],items[j],metric);
            next_best_clust=find_nbcluster(clusters,j,items[j],metric);
            b=silhouette_cluster(clusters[next_best_clust],items[j],metric);
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


double obj_func(vector<data_point<double>> items,vector<double> point,string metric){
    double dist=0.0;

    for (int i=0; i < items.size();i++){
        if (metric=="euclidean")
            dist+=euclidean_dist(items[i].point,point);
        else
            dist+=cosine_similarity(items[i].point,point);
    }

    return dist/items.size();
}


vector<double> calculate_pam_centroid(cluster cl,string metric) {
    vector<data_point<double>> cluster_dat = cl.get_items();
    int size = (int) cluster_dat.size();
    vector<double> new_cl(204, 0.0);
    double dist;
    double dist_min=10000000.0;

    for(int i=0 ; i<cluster_dat.size(); i++){
        if((dist=obj_func(cl.get_items(),cluster_dat[i].point,metric))<dist_min){
            dist_min=dist;
            new_cl=cluster_dat[i].point;
            if (dist_min<250) break;
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



vector<cluster> create_kmeans_centroids(data_point<double> *dat,int k,int length,string metric){
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
                if(metric=="euclidean")
                    dist=euclidean_dist(dat[i].point,clusters1[j].get_centroid().point);
                else
                    dist=cosine_similarity(dat[i].point,clusters1[j].get_centroid().point);
                if (dist<dist_min){
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

