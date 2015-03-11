# Raspberry

A quick, parallelized quality control tool for processing NGS big data

Authors: Mohan AVSK Katta (k.krishnamohan@cgiar.org, Aamir W Khan (a.khan@cgiar.org), Dadakhalandar Doddamani (d.doddamani@cgiar.org) and Rajeev K Varshney (r.k.varshney@cgiar.org)

Center of Excellence in Genomics

ICRISAT, Hyderabad, India

## ABOUT
* Process hundreds or thousands of samples 
* Developed in C language using HTSlib (http://htslib.org) library with a focus on speed and parallelism.
* Works and tested with compressed(gzip) or uncompressed Illumina MiSeq and HiSeq FASTQ paired/single end reads.
* The package includes a static binary (bin/raspberry) compiled on x86_64 platform in case you want to use it standalone; otherwise you may have to compile

## HELP / USAGE
```
After installing just type raspberry at shell prompt
$ raspberry
Raspberry is a fast QC tool for parallel and batch processing of NGS reads in FASTQ format. The tool accepts both compressed and decompressed FASTQ format files. It has been developed and tested with data from Illumina HiSeq and Miseq platform. For more details just run raspberry at shell  

  Computational Genomics Group, CEG, ICRISAT, Patancheru, India 2015
Usage: raspberry [-p <int>] [-t <int>] *.fastq.gz | *.fastq
Options 
-p       phred offset [default: 33]
-t       number of threads [default: as available on the machine]
```

## COMPILE and INSTALL (IN SHORT)
do the following steps in de-compressed / cloned dir
```
cd Raspberry
cmake .
make          (This will make raspberry and place it in local path ./bin/raspberry)
make install  (This will put raspberry binary in the /usr/local/bin path)
```
You should see a binary file called "raspberry" in bin dir.
copy it to your $HOME/bin or system wide /usr/local/bin

## DETAILED INSTALL INSTRUCTIONS 

1) CONFIGURE RASPBERRY 
$ cd Raspberry
$ cmake .
-- The C compiler identification is GNU 4.9.1
-- The CXX compiler identification is GNU 4.9.1
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
CMake Warning (dev) at CMakeLists.txt:9 (link_directories):
  This command specifies the relative path

    ./include/judy-1.0.5/src/obj/.libs

  as a link directory.

  Policy CMP0015 is not set: link_directories() treats paths relative to the
  source dir.  Run "cmake --help-policy CMP0015" for policy details.  Use the
  cmake_policy command to set the policy and suppress this warning.
This warning is for project developers.  Use -Wno-dev to suppress it.

-- Configuring done
-- Generating done
-- Build files have been written to: /mnt/das/ngs/test/Raspberry

2) BUILD THE PROJECT

$ make 
Scanning dependencies of target raspberry
[100%] Building C object CMakeFiles/raspberry.dir/qc.c.o
Linking C executable bin/raspberry
[100%] Built target raspberry

3) INSTALL RASPBERRY 

$ sudo make install
[sudo] password for km: 
[100%] Built target raspberry
Install the project...
-- Install configuration: "Release"
-- Installing: /usr/local/bin/raspberry

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
OR
```
Using 20 processors  and with an base quality offset of 64 
$raspberry -t 20 -p 64 *.fastq.gz
```

NOTE : The output from each file is emitted from parallel threads in the same order as given on command line

## MISCELLANEOUS UTILS

Along with the stats, the run produces a file named "read_lengths.txt" which can be used to plot a histogram of read length distribution. A helper python script "read_length_distribution.py" is provided in "utils" dir to plot this histogram.

## LICENSE 

This software is released under GPL v3.
