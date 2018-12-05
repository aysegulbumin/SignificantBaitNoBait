//
// Created by aysegul on 11/8/18.
//

#include <sstream>
#include <map>
#include <algorithm>
#include <set>
#include <functional>
#include <cmath>
#include <iostream>
#include <fstream>
#include "Merge.h"
#include <chrono>



using namespace std::chrono;

using namespace std;



int merge2fastasinto1 (int argc, char** argv)
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    ifstream myfile;
    ifstream myfile2;
    string line;
    myfile.open(argv[1]);
    myfile2.open(argv[2]);
    //myfile.open("/ufrc/boucher/aysegul.bumin/ReadCompare/BaitKmerBeefUMI_Partial1.fasta");
    //myfile2.open("/ufrc/boucher/aysegul.bumin/ReadCompare/NoBaitKmerBeefUMI_Partial1.fasta");

    //myfile.open("/home/aysegul/CLionProjects/some/BaitKmerBeefUMI.fasta");
    //myfile2.open("/home/aysegul/CLionProjects/some/NoBaitKmerBeefUMI.fasta");
    map <string, int > kmers;
    if (myfile.is_open()) {

        while (getline(myfile, line)) {
            if (line[0] != '>') {
                kmers[line]=1;
            }

        }
        myfile.close();

    }

    if (myfile2.is_open()) {

        while (getline(myfile2, line)) {
            if (line[0] != '>') {
                kmers[line]=1;
            }

        }
        myfile2.close();

    }
    ofstream b;
    //b.open("/ufrc/boucher/aysegul.bumin/ReadCompare/KmersBeefUMI_Partial1.fasta");
    b.open(argv[3]);
    //b.open("/home/aysegul/CLionProjects/some/BaitNoBaitKmersBeefUMI.txt");
    int c=0;
    for(auto elem:kmers)
    {
        c++;
        b<<">"<<c<<"\n";
        b<<elem.first<<"\n";
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<seconds>( t2 - t1 ).count();
    cout<<"CPU Time: "<<duration<<" seconds. \n";

    return 0;
}