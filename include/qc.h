#include<zlib.h>
#include<stdio.h>
#include<inttypes.h>
#include "htslib/kseq.h"
//#define offset 33
KSEQ_INIT(gzFile, gzread);
#define SUMMARY_TYPE \
typedef struct { \
    uint64_t A, T, G, C, N, read_len_min, read_len_max, nbases, nrecords, total_bp, Q20, Q30; \
    double read_len_avg, read_len_median, GC; \
    int base_qual_min, base_qual_max; \
}summary_t;
SUMMARY_TYPE;

#define COUNTS_INIT \
summary_t* counts_init(){ \
    summary_t *summary; \
    summary = (summary_t*) malloc(sizeof(summary_t)); \
    return summary; \
} \
void counts_default(summary_t *summary){ \
    summary->A = summary->T = summary->G = summary->C = summary->N = summary->nbases = summary->base_qual_max = summary->nrecords = summary->read_len_max = summary->total_bp = summary->Q20 = summary->Q30 = 0; \
    summary->read_len_avg = summary->read_len_median = summary->GC = 0.0; \
    summary->base_qual_min = summary->read_len_min = 10000000000; \
}\
void free_summary(summary_t *summary){ \
    free(summary); \
} \
void get_gc_content(summary_t *summary){ \
    summary->GC = (summary->G + summary->C)*100.0/summary->nbases; \
}\
void process(kseq_t* ks, summary_t *summary, int offset){ \
    uint64_t k; \
    for(k = 0;k < ks->seq.l;++k){ \
        char base = ks->seq.s[k];\
        base == 'A'?summary->A++:base == 'T'?summary->T++:base=='G'?summary->G++:base=='C'?summary->C++:summary->N++; \
        if (((int)ks->qual.s[k] - offset) >= 30) {\
            summary->Q30++;\
            summary->Q20++;\
        }\
        else if (((int)ks->qual.s[k] - offset) >= 20) \
            summary->Q20++;\
        if (summary->base_qual_min > ks->qual.s[k]) \
            summary->base_qual_min = ks->qual.s[k]; \
        if (summary->base_qual_max < ks->qual.s[k]) \
            summary->base_qual_max = ks->qual.s[k]; \
    }\
    if (summary->read_len_max < ks->seq.l){ \
        summary->read_len_max = ks->seq.l; \
    }\
    if (summary->read_len_min > ks->seq.l){ \
        summary->read_len_min = ks->seq.l; \
    } \
    summary->nbases += ks->seq.l; \
    summary->nrecords++;\
}\
void write_readlengths(FILE* fh, size_t* read_len){\
    fprintf(fh, "%zu\n", *read_len);\
}\
void stats(char* fastq, int offset){\
    summary_t *summ;\
    summ = counts_init();\
    counts_default(summ);\
    char rlengths_file[1024]="";\
    char phred_scores_file[1024]="";\
    snprintf(rlengths_file, sizeof rlengths_file, "%s%s", fastq,".rlen");\
    snprintf(phred_scores_file, sizeof phred_scores_file, "%s%s", fastq,".phred");\
    FILE *fh = fopen(rlengths_file,"w+");\
    gzFile fp = gzopen(fastq, "r");\
    kseq_t *ks = kseq_init(fp);\
    while(kseq_read(ks)>=0){\
        process(ks, summ, offset);\
        write_readlengths(fh, &ks->seq.l);\
    }\
    kseq_destroy(ks);\
    gzclose(fp);\
    get_gc_content(summ);\
    printf("File name : %s\n", fastq);\
    printf("Total bases : " "%" PRIu64 "\n",summ->nbases);\
    printf("Total reads : " "%" PRIu64 "\n",summ->nrecords);\
    printf("%% bases >=Q20 : %.3f\n", summ->Q20*100.0/summ->nbases);\
    printf("%% bases >=Q30 : %.3f\n", summ->Q30*100.0/summ->nbases);\
    printf("Average read length : " "%.3f\n", summ->nbases*1.0/summ->nrecords);\
    printf("Read length range : " "%" PRIu64 " .. " "%" PRIu64 "\n", summ->read_len_min, summ->read_len_max);\
    printf("Quality range : " "%d .. %d\n" , summ->base_qual_min, summ->base_qual_max);\
    printf("Phred range : " "%d .. %d\n" , summ->base_qual_min - offset, summ->base_qual_max - offset);\
    printf("Offset : %d\n", offset);\
    printf("A : " "%" PRIu64 "\n", summ->A);\
    printf("T : " "%" PRIu64 "\n", summ->T);\
    printf("G : " "%" PRIu64 "\n", summ->G);\
    printf("C : " "%" PRIu64 "\n", summ->C);\
    printf("N : " "%" PRIu64 "\n", summ->N);\
    printf("percent G-C content : %.3f\n", summ->GC);\
    free(summ);\
    fclose(fh); \
}
