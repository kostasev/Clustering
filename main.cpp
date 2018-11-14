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

void get_cfg(std::string ,int &, int &, int &);

using namespace std;

int main(int argc, char** argv) {
    int c;
    int num_clusters = 5;
    int num_hfunc = 4;
    int num_htables = 5;
    string input, conf, output, metric;
    get_cfg(num_clusters,num_hfunc,num_htables);

    /* Reading Arguments from command line */
    while ((c = getopt(argc, argv, "i:c:o:d")) != -1) {
        switch (c) {
            case 'i':
                input = optarg;
                break;
            case 'c':
                conf =  optarg;
                break;
            case 'o':
                output = optarg;
                break;
            case 'd':
                metric = optarg;
                if ((metric != "cosine") && (metric != "euclidean")) {
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
    return 0;
}

void get_cfg(string inputf, int &clusters, int &hfunc, int &htables) {
    ifstream file;
    file.open (inputf);
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