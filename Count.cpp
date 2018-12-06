//
// Created by aysegull on 10/22/18.
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
#include<bits/stdc++.h>
using namespace std;
#include <chrono>



using namespace std::chrono;

int countFreq(string &pat, string &txt)
{
    int M = pat.length();
    int N = txt.length();
    int res = 0;

    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++)
    {
        /* For current index i, check for
           pattern match */
        int j;
        for (j = 0; j < M; j++)
            if (txt[i+j] != pat[j])
                break;

        // if pat[0...M-1] = txt[i, i+1, ...i+M-1]
        if (j == M)
        {
            res++;
            j = 0;
        }
    }
    return res;
}



int Count(int argc, char** argv)
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    ifstream myfile2;
    myfile2.open(argv[2]);

    string line2;
    string line;
    // int columns=stoi(argv[3]);
    string a=argv[4];
    ofstream output;
    output.open(a);
    if (myfile2.is_open()) {

        while (getline(myfile2, line2)) {


            if(line2[0]=='>')
            {

            }
            else
            {

                ifstream myfile;
                myfile.open(argv[3]);
                int c=0;
                if (myfile.is_open()) {

                    while (getline(myfile, line)) {

                        if(line[0]=='>')
                        {

                        }
                        else
                        {
                            c++;
                            // if(c<=columns)
                            // {
                            string txt = line2;
                            string pat = line;
                            output << countFreq(pat, txt)<<" ";
                            // }
                            // else
                            // {
                            //     break;
                            // }

                        }

                    }
                    output<<"\n";
                    myfile.close();
                }

            }
        }
        output.close();
        myfile2.close();
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<seconds>( t2 - t1 ).count();
    cout<<"CPU Time: "<<duration<<" seconds. \n";
    return 0;

}