//
// Created by aysegull on 8/15/18.
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
#include "KmerMerge.h"


using namespace std::chrono;
using namespace std;

vector<vector<int>> counts_vector;
vector<string> kmer_vector;
int dumping_count=0;
ofstream output;
int countzeros=0;
vector<string> convertbytab(string input)
{
    vector<char> v;

    istringstream ss(input);
    string token;
    vector<string> line_vector;
    while(std::getline(ss, token, '\t'))
    {
        line_vector.push_back(token);
    }
    return line_vector;
}

vector<string> convertbyspace(string input)
{
    vector<char> v;

    istringstream ss(input);
    string token;
    vector<string> line_vector;
    while(std::getline(ss, token, ' '))
    {
        line_vector.push_back(token);
    }
    return line_vector;
}

int call_compare(string kmers[], int counts[], ifstream myfiles[], int m_files, int more_than, ofstream & output)
{


    bool all_empty=false;



    while(!all_empty) //if all of them are not null this means we are not in the end of every file
    {
        all_empty=true;

        if(kmer_vector.size()==100000)
        {
            //This part is implemented to not to dump each and every time. It dumps to the output file whenever the size reaches to 100000
            dumping_count++;
            cout<< "Dumping the "<< dumping_count<<"th time..."<<endl;
            for(int i=0;i<kmer_vector.size();i++)
            {
                output<<kmer_vector[i]<<",";
                for(int k=0 ;k<m_files;k++)
                {
                    if(k!=m_files-1)
                    {
                        output<<counts_vector[i][k]<<",";
                    }
                    else
                    {
                        output<<counts_vector[i][k]<<"\n";
                    }


                }

            }
            kmer_vector.clear();
            counts_vector.clear();
        }
        vector<string> temp_vec;
        vector<int> temp;
        vector<int> min_indices;

        string temp_line;
        string temp_kmer;
        string min_kmer="";
        for(int i=0;i<31;i++)
        {
            //Assuming that we are dealing with kmers of size 31, works for some other as well since any string starting with Z is alphabetically > than any kmer.
            min_kmer=min_kmer+"Z";
        }

        int temp_count;
        /*bool check=true;
        for(int k=0;k<m_files;k++)
        {
                if(counts[k]==1 || counts[k]==0)
                {
                        check=check&&true;
                }
                else
                {
                        check=check&&false;
                }
        }
        if(check)
        {
                countzeros++;
        }*/
        for(int i=0;i<m_files;i++)
        {
            all_empty=all_empty && (kmers[i].empty()); //all of them are null
        }
        for(int k=0;k<m_files;k++)
        {
            //Here the files that have the alphabetically minimum kmers. Can be tought as there is a pointer to the first line of each file. And what is found is the smallest kmers. k denotes the file id
            if(!kmers[k].empty())
            {
                if(kmers[k].compare(min_kmer)<0)
                {
                    min_indices.clear();
                    min_kmer=kmers[k];
                }
                if(kmers[k].compare(min_kmer)==0)
                {
                    min_indices.push_back(k);
                }
            }
        }
        if(min_indices.size()>=more_than)
        {
            //this means there are 10 or more of this minimum kmer which is worth reporting.
            //********************REPORTING*************************
            temp.clear();
            for(int k=0;k<m_files;k++)
            {
                temp.push_back(0);
            }

            for(int i=0;i<min_indices.size();i++)
            {
                temp[min_indices[i]]=counts[min_indices[i]];
            }
            kmer_vector.push_back(kmers[min_indices[0]]);
            counts_vector.push_back(temp);
            //******************************UPDATE*************************
            for(int i=0;i<min_indices.size();i++)
            {
                temp_line="";
                temp_kmer="";
                temp_count=0;
                if(getline(myfiles[min_indices[i]],temp_line))
                {
                    temp_vec.clear();
                    std::size_t found = temp_line.find('\t');
                    if (found!=std::string::npos)
                    {
                        //If separated by tab
                        temp_vec=convertbytab(temp_line);
                    }
                    else
                    {
                        //If separated by space
                        temp_vec=convertbyspace(temp_line);
                    }

                    temp_kmer=temp_vec[0];
                    temp_count=stoi(temp_vec[1]);

                }
                else
                {
                    //this particular file has reached the end of file
                    temp_kmer="";
                    temp_count=0;
                }

                kmers[min_indices[i]]=temp_kmer;
                counts[min_indices[i]]=temp_count;

            }


        }
        else
        {
            //there are less than 10 occurences of this k-mer but we will still call the function with the new updated parameters
            //******************************UPDATE*************************
            for(int i=0;i<min_indices.size();i++)
            {
                temp_line="";
                temp_kmer="";
                int temp_count;
                if(getline(myfiles[min_indices[i]],temp_line))
                {
                    temp_vec.clear();
                    std::size_t found = temp_line.find('\t');
                    if (found!=std::string::npos)
                    {
                        temp_vec=convertbytab(temp_line); //If separated by tab
                    }
                    else
                    {
                        temp_vec=convertbyspace(temp_line); // If separated by space
                    }
                    temp_kmer=temp_vec[0];
                    temp_count=stoi(temp_vec[1]);

                }
                else
                {
                    //this particular file has reached the end of file
                    temp_kmer="";
                    temp_count=0;
                }

                kmers[min_indices[i]]=temp_kmer;
                counts[min_indices[i]]=temp_count;

            }

        }
    }

    for(int i=0;i<kmer_vector.size();i++)
    {
        //Dumping out the rest at the very end of the function. Maybe kmer_vector size is not big enough to dump but we still have to dump them to the output file.
        output<<kmer_vector[i]<<",";
        for(int k=0 ;k<m_files;k++)
        {
            if(k!=m_files-1)
            {
                output<<counts_vector[i][k]<<",";
            }
            else
            {
                output<<counts_vector[i][k]<<"\n";
            }


        }

    }
    kmer_vector.clear();
    counts_vector.clear();
    return 0;
}



int Co (int argc, char** argv)
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    vector <string>  file_list;
    if(argc<5)
    {
        cout<<"Please provide Input parameters correctly."<<endl;
        return 0;
    }
    int more_than=stoi(argv[2]);
    string name=argv[3];
    int m_files=stoi(argv[4]);
    if(argc<5+m_files)
    {
        cout<<"Please provide Input parameters correctly."<<endl;
        return 0;
    }
    for (int i=1; i<m_files+1;i++)
    {
        file_list.push_back(argv[i+4]); //I will start with parameters 2 1 2 //meaning 2 files namely 1 2
    }

    ifstream inputFile[m_files];

    for (int i = 0; i < m_files; i++)
    {
        inputFile[i].open(file_list[i]);
        //inputFile[i].open("/home/aysegull/ClionProjects/SignificantBaitNoBait/Sorted"+file_list[i]+".txt");
        //inputFile[i].open("/ufrc/boucher/aysegul.bumin/Kmer"+file_list[i]+".txt");
        //inputFile[i].open("/ufrc/boucher/aysegul.bumin/SortedJelly"+file_list[i]+".txt");
    }
    output.open(name);
    //output.open("/home/aysegull/ClionProjects/SignificantBaitNoBait/All"+name+".txt");
    //output.open("/ufrc/boucher/aysegul.bumin/ReadCompare/All"+name+".txt");
    output<<"\t,";
    for(int i=0;i<m_files;i++)
    {
        if(i!=m_files-1)
        {
            output<<file_list[i]<<",";
        }
        else
        {
            output<<file_list[i]<<"\n";
        }
    }
    string lines[m_files];
    bool first_lines_fine=true;
    for (int i = 0; i < m_files; i++)
    {
        first_lines_fine= first_lines_fine && bool(inputFile[i].is_open() && getline(inputFile[i],lines[i]));
    }

    vector<string> myvecs[m_files];
    string kmers[m_files];
    int counts[m_files];
    if(first_lines_fine)
    {
        for (int i = 0; i < m_files; i++)
        {
            std::size_t found = lines[i].find('\t');
            if (found!=std::string::npos)
            {

                myvecs[i]=convertbytab(lines[i]);
            }
            else
            {
                myvecs[i]=convertbyspace(lines[i]);
            }
            //myvecs[i]=convertbytab(lines[i]);
            kmers[i]=myvecs[i][0];
            //cout<<myvecs[i][1]<<endl;

            counts[i]=stoi(myvecs[i][1]);
        }
        //You may end up here even if only one file is not empty or if one file is open and not empty.
        /*bool check=true;
        for(int k=0;k<m_files;k++)
        {
            if(counts[i]==1 || counts[i]==0)
            {
                check=check&&true;
            }
            else
            {
                check=check&&false;
            }
        }
            if(check)
        {
            countzeros++;
        }*/
        call_compare(kmers, counts, inputFile, m_files, more_than, output);


    }
    for (int i = 0; i < m_files; i++)
    {
        //close each file
        if (inputFile[i].is_open()) {inputFile[i].close();}
    }




    output.close();

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<seconds>( t2 - t1 ).count();
    cout<<"CPU Time: "<<duration<<" seconds. \n";


    return 0;
}
