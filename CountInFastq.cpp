//
// Created by aysegull on 12/8/18.
//

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
#include <vector>
#include<bits/stdc++.h>
#include <chrono>

using namespace std;




using namespace std::chrono;
int countFreq2(string &pat, string &txt)
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


int CountInFastq(int argc, char** argv)
{

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    ifstream myfile2;
    myfile2.open(argv[2]);

    string line2;
    string line;
    // int columns=stoi(argv[3]);
    string a=argv[5];
    ofstream output;
    output.open(a);
    int count=0;
    if (myfile2.is_open()) {

        while (getline(myfile2, line2)) {

            count++;
            if(count==4)
            {
                count=0;

            }
            else if(count==2)
            {

                ifstream myfile;
                myfile.open(argv[4]);
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
                            output << countFreq2(pat, txt)<<" ";
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

        myfile2.close();
    }


    ifstream myfile3;
    myfile3.open(argv[3]);
    count=0;
    if (myfile3.is_open()) {

        while (getline(myfile3, line2)) {

            count++;
            if(count==4)
            {
                count=0;

            }
            else if(count==2)
            {

                ifstream myfile;
                myfile.open(argv[4]);
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
                            output << countFreq2(pat, txt)<<" ";
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

        myfile3.close();
    }
    output.close();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<seconds>( t2 - t1 ).count();
    cout<<"CPU Time: "<<duration<<" seconds. \n";
    return 0;

}
