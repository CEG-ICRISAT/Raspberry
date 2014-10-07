/*
Raspberry, a qc tool for processing large sets of fastq files quickly
Authors:  AVSK Mohan Katta, Aamir  Khan, Rajeev Varshney
Center of Excellence in Genomics
ICRISAT, India
License GPL V3
*/
#include<stdio.h>
#include<omp.h>
#include "qc.h"
COUNTS_INIT(OFFSET);
int main(int argc, char** argv){
int k;
#pragma omp parallel
{
#pragma omp for ordered 
for(k=1; k < argc; ++k){
    stats(argv[k]);
}
}
return 0;
}
