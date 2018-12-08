all:
	g++ -o main -std=c++11 main.cpp KmerMerge.cpp KmerMerge.h FoldChange.cpp FoldChange.h Merge.cpp Merge.h Count.cpp Count.h CountInFastq.cpp CountInFastq.h
