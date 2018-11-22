//
// Created by kevangel on 22/11/18.
//

#include "cluster.h"


cluster::cluster() {}

void cluster::set_centroid(vector<double> cen){
    this->centroid=cen;
}

vector<double> cluster::get_centroid(){
    return this->centroid;
}

void cluster::add_item(data_point<double> item){
    this->clitems.push_back(item);
}

vector<data_point<double>> cluster::get_items(){
    return this->clitems;
}

void cluster::empty_clitems() {
    this->clitems.clear();
}