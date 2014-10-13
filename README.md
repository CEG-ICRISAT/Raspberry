# Raspberry

A quick, parallelized quality control tool for processing NGS big data

Authors: Mohan AVSK Katta (k.krishnamohan@cgiar.org, Aamir W Khan (a.khan@cgiar.org), Dadakhalandar Doddamani (d.doddamani@cgiar.org) and Rajeev K Varshney (r.k.varshney@cgiar.org)

Center of Excellence in Genomics
ICRISAT, Hyderabad, India

## ABOUT
* Developed in C language using HTSlib (http://htslib.org) library with a focus on speed and parallelism.
* Works and tested with compressed(gzip)/uncompressed Illumina MiSeq and HiSeq FASTQ paired/single end reads.
* The package includes a static compiled binary file on x86_64 platform
* Helpful to process hundreds or thousands of samples

## COMPILE and INSTALL
do the following in decompressed/cloned dir
```
cd Raspberry
cmake .
make
```
You should see the binary raspberry in bin dir.
copy it to your $HOME/bin or system wide /usr/local/bin

## USAGE

At the shell prompt, do
```
$raspberry read1.fastq > output
```
OR 
```
$raspberry read1.fastq.gz > output
```
OR 
```
$raspberry *.gz  > output 
```
OR 
```
$raspberry *.fastq > output 
```
NOTE : The output from each file is emitted from parallel threads in order

## MISCELLANEOUS UTILS

Along with the stats, the run produces a file named "read_lengths.txt" which can be used to plot a histogram of read length distribution. A helper python script "read_length_distribution.py" is provided in "utils" dir to plot this histogram.

## LICENSE 

This software is released under GPL v3.
