#include <iostream>
#include "KmerMerge.h"
#include "FoldChange.h"
#include "Count.h"
#include "Merge.h"

using namespace std;

int main(int argc, char** argv) {
    int n=stoi(argv[1]);
    switch (n)
    {
        case 0:
            cout<<"Merging the Kmer Counts."<<endl;
            Co (argc, argv); //0 1 /home/aysegull/ClionProjects/SignificantBaitNoBait/AllTest.txt 4 /home/aysegull/ClionProjects/SignificantBaitNoBait/Sorted1.txt /home/aysegull/ClionProjects/SignificantBaitNoBait/Sorted2.txt /home/aysegull/ClionProjects/SignificantBaitNoBait/Sorted3.txt  /home/aysegull/ClionProjects/SignificantBaitNoBait/Sorted4.txt
            break;
        case 1:
            cout<<"Calculating the Log Fold Change."<<endl;
            FoldChange (argc, argv); // 1 2 1 2 /home/aysegull/ClionProjects/SignificantBaitNoBait/AllTest.txt  /home/aysegull/ClionProjects/SignificantBaitNoBait/Bait.fasta /home/aysegull/ClionProjects/SignificantBaitNoBait/NoBait.fasta
            break; // 1 2 1 2 /home/aysegull/ClionProjects/SignificantBaitNoBait/HeadAll.txt  /home/aysegull/ClionProjects/SignificantBaitNoBait/HeadBait.fasta /home/aysegull/ClionProjects/SignificantBaitNoBait/HeadNoBait.fasta
        case 2:
            cout<<"Merging 2 fasta files into 1 fasta file."<<endl;
            merge2fastasinto1(argc, argv); //2 /home/aysegull/ClionProjects/SignificantBaitNoBait/Merge1.fasta /home/aysegull/ClionProjects/SignificantBaitNoBait/Merge2.fasta /home/aysegull/ClionProjects/SignificantBaitNoBait/Merged.fasta
            break;
        case 3:
            //3 /home/aysegull/ClionProjects/SignificantBaitNoBait/HeadNotContam5.fasta  /home/aysegull/ClionProjects/SignificantBaitNoBait/HeadBait.fasta /home/aysegull/ClionProjects/SignificantBaitNoBait/MatrixBait.txt
            cout<<"Counting given Kmers in fasta file."<<endl;
            Count(argc, argv);// 3 /home/aysegull/ClionProjects/SignificantBaitNoBait/NotContamTest.fasta /home/aysegull/ClionProjects/SignificantBaitNoBait/KmerTest.fasta /home/aysegull/ClionProjects/SignificantBaitNoBait/InputTest.txt
            break;
        default:
            cout<<"Please select a relevant mode."<<endl;
    }

    return 0;
}