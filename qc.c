/*
Raspberry, a qc tool for processing large sets of fastq files quickly
Authors:  AVSK Mohan Katta, Aamir  Khan, Dadakhalandar Doddamani, Rajeev Varshney
Center of Excellence in Genomics
ICRISAT, India
License GPL V3
*/
#include<stdio.h>
#include<stdlib.h>
#include<Judy.h>
#include<omp.h>
#include "qc.h"
void help(){
fprintf(stderr, "Raspberry is a fast QC tool for parallel and batch processing of NGS reads in FASTQ format.\
 The tool accepts both compressed and decompressed FASTQ format files.\
 It has been developed and tested with data from Illumina HiSeq and Miseq platform.\
 For more details just run raspberry at shell  \n\n \
 Computational Genomics Group, CEG, ICRISAT, Patancheru, India 2015\
");
fprintf(stderr, "\n");
fprintf(stderr, "Usage: raspberry [-p <int>] [-t <int>] *.fastq.gz | *.fastq\n");
fprintf(stderr, "Options \n-p\t phred offset [default: 33]\n");
fprintf(stderr, "-t\t number of threads [default: as available on the machine]\n");
}
int offset = 33;
COUNTS_INIT;
void run_parallel(int offset, int n_fastq_files, Pvoid_t PJLArray, int nt){
    int k;
    PWord_t PValue;
    if (!nt) nt = omp_get_num_procs();
    omp_set_num_threads(nt);
    #pragma omp parallel
    {
    //printf("number of procs: %d\n", nt); 
    #pragma omp for ordered 
    for(k=0; k < n_fastq_files; ++k){
        JLG(PValue, PJLArray, k); 
        stats((unsigned char*) *PValue, offset);
    }
    }
}

int main(int argc, char** argv){

int key, nthreads = 0;
//process options
while((key = getopt(argc, argv, "p:t:")) >= 0){
    switch(key){
    case 'p':  
        offset = atoi(optarg);
        break;
    case 't':
        nthreads = atoi(optarg);
        break;        
    default:
        help();
        break;
        return 0;
    }
}
if(optind == argc){
    help();
    return 0;
}
//remaining non-option args
    int n = argc - optind; 
    Pvoid_t PJLArray = (Pvoid_t) NULL;
    PWord_t PValue;
    Word_t Index, Rc_word;
    Word_t n_fastq_files;
// read the rest of the args into an array
    for(Index=0; Index < n; ++Index){
        JLI(PValue, PJLArray, Index);
        *PValue = (Word_t) argv[optind++];
    }
//find total # indexes
    JLC(n_fastq_files, PJLArray, 0, -1);
    //printf("number of files on cmd line:%lu\n", n_fastq_files);
//run main task
    run_parallel(offset, n_fastq_files, PJLArray, nthreads);
    JLFA(Rc_word, PJLArray);
return 0;
}
