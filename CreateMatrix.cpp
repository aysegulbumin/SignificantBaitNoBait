//
// Created by aysegull on 12/19/18.
//



#include <sstream>
#include <map>
#include <algorithm>
#include <set>
#include <functional>
#include <cmath>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include<bits/stdc++.h>
#include <chrono>
#include "CreateMatrix.h"

using namespace std;


using namespace std::chrono;

map<string,int> significant_kmers;

void InitializeMap(string name)
{
    significant_kmers.clear();
    ifstream kmerfile;
    kmerfile.open(name); //kmer file
    string linekmer;
    if (kmerfile.is_open()) {

        while (getline(kmerfile, linekmer)) {
            if(linekmer[0]=='>')
            {

            }
            else
            {
                significant_kmers[linekmer];
                significant_kmers[linekmer]=0;

            }

        }
        kmerfile.close();
    }

}
void PrintMap(string output)
{
    ofstream outputfile;
    outputfile.open(output,std::ios::app);
    for(auto item:significant_kmers)
    {

        outputfile<<item.second<<" ";

    }
    outputfile<<"\n";
    outputfile.close();

}

void FillMap(string sequence)
{
    for(int i=0;i<sequence.size()-31;i++)
    {
        string r = sequence.substr(i, 31);
        if (significant_kmers.find(r) != significant_kmers.end())
        {
            //found
            significant_kmers[r]++;
        }

    }
}


int CreateMatrix(int argc, char** argv) {

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

//3 /home/aysegull/ClionProjects/SignificantBaitNoBait/5f.fastq /home/aysegull/ClionProjects/SignificantBaitNoBait/5r.fastq  /home/aysegull/ClionProjects/SignificantBaitNoBait/Merged.fasta /home/aysegull/ClionProjects/SignificantBaitNoBait/OutputMatrix5.txt
    InitializeMap(argv[4]);
    //PrintMap(argv[5]); //OutputFile

    int count=0;


    ifstream myfile;
    myfile.open(argv[2]); //fastq file
    string line;
    if (myfile.is_open()) {

        while (getline(myfile, line)) {
            count++;
            if(count==4)
            {
                count=0;

            }
            else if(count==2)
            {
                FillMap(line);
                PrintMap(argv[5]);
                InitializeMap(argv[4]);
            }

        }
        myfile.close();
    }
    count=0;

    ifstream myfile2;
    myfile2.open(argv[3]); //fastq file 2
    string line2;
    if (myfile2.is_open()) {

        while (getline(myfile2, line2)) {
            count++;
            if(count==4)
            {
                count=0;

            }
            else if(count==2)
            {
                FillMap(line2);
                PrintMap(argv[5]);
                InitializeMap(argv[4]);
            }

        }
        myfile2.close();
    }








    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<seconds>( t2 - t1 ).count();
    cout<<"CPU Time: "<<duration<<" seconds. \n";

    return 0;


}
