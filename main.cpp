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

void get_cfg(int &, int &, int &);

using namespace std;

int main(int argc, char** argv) {
    int num_clusters = 5;
    int num_hfunc = 4;
    int num_htables = 5;
    get_cfg(num_clusters,num_hfunc,num_htables);


    return 0;
}

void get_cfg(int &clusters, int &hfunc, int &htables) {
    ifstream file;
    file.open ("../cluster.conf");
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
}