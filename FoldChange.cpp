//
// Created by aysegull on 8/28/18.
//

#include <sstream>
#include <map>
#include <algorithm>
#include <set>
#include <functional>
#include <cmath>
#include <iostream>
#include <fstream>
#include "FoldChange.h"
#include <chrono>



using namespace std::chrono;
using namespace std;

vector<string> convertbycomma(string input)
{
    vector<char> v;

    istringstream ss(input);
    string token;
    vector<string> line_vector;
    while(std::getline(ss, token, ','))
    {
        line_vector.push_back(token);
    }
    return line_vector;
}

void eraseAllSubStr(std::string & mainStr, const std::string & toErase)
{
    size_t pos = std::string::npos;

    // Search for the substring in string in a loop until nothing is found
    while ((pos  = mainStr.find(toErase) )!= std::string::npos)
    {
        // If found then erase it from string
        mainStr.erase(pos, toErase.length());
    }
}
int FoldChange (int argc, char** argv)
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    ifstream myfile;
    string line;
    vector<int> bait_indices;
    vector<int> no_bait_indices;
    int size=stoi(argv[1]);

    for(int i=0;i<size/2;i++)
    {
        bait_indices.push_back(stoi(argv[2+i]));
    }
    for(int i=0;i<size/2;i++)
    {
        no_bait_indices.push_back(stoi(argv[2+(size/2)+i]));
    }
    int bait1=0;
    int nobait1=0;
    string input_file=argv[2+size];
    string bait_output_file=argv[3+size];
    string no_bait_output_file=argv[4+size];
    myfile.open(input_file);


    vector<float> log_folds;
    vector<string> all_baits;
    vector<string> all_nobaits;
    float total_bait=0;
    float total_nobait=0;
    int countzeros=0;
    int count=0;
    ofstream output;
    output.open(bait_output_file);
    ofstream output2;
    output2.open(no_bait_output_file);
    int kmer_bait=0;
    int kmer_nobait=0;

    if (myfile.is_open())
    {

        while ( getline (myfile,line) )
        {
            total_bait=0;
            total_nobait=0;
            count++;
            if(count==1)
            {
                //skip
            }
            else
            {
                vector<string> myvec=convertbycomma(line);
                string templine="";
                for(int k=1;k<myvec.size();k++)
                {
                    templine=templine+myvec[k];
                }

                eraseAllSubStr(templine, "1");
                eraseAllSubStr(templine,   "0");
                if(templine.size()==0)
                {
                    countzeros++;
                }

                for(int k=0;k<bait_indices.size();k++)
                {
                    total_bait=total_bait+stof(myvec[bait_indices[k]]);
                    total_nobait=total_nobait+stof(myvec[no_bait_indices[k]]);
                }
                // cout<<  "Total Bait"<<total_bait<<"Total NoBait"<< total_nobait<<endl;

                if(total_bait==0)
                {
                    all_nobaits.push_back(line);
                    kmer_nobait++;
                    if(total_nobait!=1)
                    {
                        output2<<">"+to_string(kmer_nobait)+"\n";
                        output2<<myvec[0]<<"\n";
                    }

                }
                else if(total_nobait==0)
                {
                    //cout<<myvec[0]<<"\t"<<total_bait<<"\t"<<total_nobait<<endl;
                    all_baits.push_back(line);
                    kmer_bait++;
                    if(total_bait!=1)
                    {
                        output<<">"+to_string(kmer_bait)+"\n";
                        output<<myvec[0]<<"\n";
                    }

                }
                else
                {
                    log_folds.push_back(log(total_bait/total_nobait));
                    if(log(total_bait/total_nobait)>=3)
                    {
                        kmer_bait++;
                        output<<">"+to_string(kmer_bait)+"\n";
                        output<<myvec[0]<<"\n";

                    }
                    else if(log(total_bait/total_nobait)<=-3)
                    {
                        kmer_nobait++;
                        output2<<">"+to_string(kmer_nobait)+"\n";
                        output2<<myvec[0]<<"\n";

                    }
                }

            }


        }
        myfile.close();
        output.close();
        output2.close();


    }
    cout<<"All Zeros and ones....."<<countzeros<<endl;
    cout<<"All Baits ........"<<all_baits.size()<<endl;
    cout<<"All No Baits ....."<<all_nobaits.size()<<endl;
    vector<int> counts;
    for(int i=0;i<10;i++)
    {
        counts.push_back(0);
    }
    auto max = *max_element(std::begin(log_folds), std::end(log_folds));
    auto min = *min_element(std::begin(log_folds), std::end(log_folds));
    float add=(max-min)/10;
    vector<float> log_fold_vals;
    for(int i=0;i<10;i++)
    {
        log_fold_vals.push_back(min+i*add);
    }


    for( int i=0;i<=log_folds.size();i++)
    {
        float a=log_folds[i];

        if(a>min && a<=min+add)
        {
            counts[0]++;
        }
        else if(a>min+add && a<=min+2*add)
        {
            counts[1]++;
        }
        else if(a>min+2*add && a<=min+3*add)
        {
            counts[2]++;
        }

        else if(a>min+3*add && a<=min+4*add)
        {
            counts[3]++;
        }
        else if(a>min+4*add && a<=min+5*add)
        {
            counts[4]++;
        }
        else if(a>min+5*add && a<=min+6*add)
        {
            counts[5]++;
        }
        else if(a>min+6*add && a<=min+7*add)
        {
            counts[6]++;
        }
        else if(a>min+7*add && a<=min+8*add)
        {
            counts[7]++;
        }
        else if(a>min+8*add && a<=min+9*add)
        {
            counts[8]++;
        }
        else if(a>min+9*add)
        {
            counts[9]++;
        }

    }
    cout<<"********************** PLOT *******************************"<<endl;
    for(int i =0;i<counts.size();i++)
    {
        cout<<log_fold_vals[i]<<"\t"<<counts[i]<<endl;
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<seconds>( t2 - t1 ).count();
    cout<<"CPU Time: "<<duration<<" seconds. \n";

    return 0;

}