//
// Created by kosti on 11/20/2018.
//

#include <cstring>
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
void feed_data_set(string input, data_point<double> *pPoint,int d) {
    char cc[1024] ;
    double dd;
    string name;
    string line;
    ifstream inputfd;
    inputfd.open (input);
    inputfd.exceptions(std::ifstream::failbit|std::ifstream::badbit);
    int i=0,j,z=0;
    cout.precision(15);
    while(z<5000){
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