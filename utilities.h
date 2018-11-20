//
// Created by kosti on 11/20/2018.
//

#ifndef PROJECT2_UTILITIES_H
#define PROJECT2_UTILITIES_H

#include <fstream>
#include <iostream>
#include <string>
#include "data_point.h"

using namespace std;

int num_columns(std::string line) ;
void get_cfg(string inputf, int &clusters, int &hfunc, int &htables) ;
void get_data_lengths(string input,int& lines, int& d) ;
void feed_data_set(string input, data_point<double> *pPoint,int d) ;

#endif //PROJECT2_UTILITIES_H
