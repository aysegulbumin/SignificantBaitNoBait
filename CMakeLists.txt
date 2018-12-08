cmake_minimum_required(VERSION 3.6)
project(SignificantBaitNoBait)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp KmerMerge.cpp KmerMerge.h FoldChange.cpp FoldChange.h Count.cpp Count.h Merge.cpp Merge.h CountInFastq.cpp CountInFastq.h)
add_executable(SignificantBaitNoBait ${SOURCE_FILES})