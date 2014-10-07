#include<stdio.h>
#include<omp.h>
#include "qc.h"
COUNTS_INIT(OFFSET);
int main(int argc, char** argv){
int k;
#pragma omp parallel num_threads(10)
{
#pragma omp for ordered 
for(k=1; k < argc; ++k){
        #pragma omp ordered
        stats(argv[k]);
}
}
return 0;
}
