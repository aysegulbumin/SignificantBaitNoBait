make
./main 0 1 MergedKmers5_8.txt 2 Kmer5.txt Kmer8.txt 
./main 1 2 1 2 1 MergedKmers5_8.txt Bait.fasta NoBait.fasta
./main 2 Bait.fasta NoBait.fasta SignificantKmers.fasta
./main 3 5f.fastq 5r.fastq SignificantKmers.fasta Bait_Matrix.txt
./main 3 8f.fastq 8r.fastq SignificantKmers.fasta NoBait_Matrix.txt

