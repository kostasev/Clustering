//
// Created by kevangel on 22/11/18.
//

#ifndef PROJECT2_CLUSTER_H
#define PROJECT2_CLUSTER_H

#import <vector>
#import "data_point.h"
using namespace std;
class cluster {
private:
    vector<double> centroid;
    vector<data_point<double>> clitems;
public:
    cluster();
    void set_centroid(vector<double>);
    vector<double> get_centroid();
    void add_item(data_point<double>);
    vector<data_point<double>> get_items();
    void empty_clitems();
};


#endif //PROJECT2_CLUSTER_H
