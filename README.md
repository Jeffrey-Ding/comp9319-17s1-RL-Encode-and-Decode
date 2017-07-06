# comp9319-17s1-RL-Encode-and-Decode
C++ code for Assignment 1 of COMP9319-Web Data Compression &amp; Search



Specification:

Your task in this assignment is to create a simple compression program that implements run-length encoding (RLE). Your program will produce a file of the minimum size using only run-length encoding. Hints on representing the runs to achieve a minimum size will be discussed in the lecture. The original input file may include any visible ASCII characters up to ASCII value 126. You can use the first bit of a byte to determine if a byte represents an ASCII character, or if it is part of a number that represents the count. 

Your C/C++ programs, called  rlencode and  rldecode, will accept either one or two arguments.  


When rlencode and rldecode accept two arguments, the first one is  the path to an input file; and the second argument is the path to an output file.  For example, for rlencode, the input file is the original input text file and the output file will be the RLE encoded file.  
As described above, a visible ASCII character is 7-bit code, with the first bit of the byte being zero. To differentiate a count from a character, a count will have the first bit on, and use the remaining 7 bits to represent the actual value. When a number is larger than 2^7, you will need to concatenate the subsequent "count" byte(s) to form the final value. You are responsible to design the representation of these counts so that you achieve the minimum encoded file size. 


When rlencode and rldecode are given with one argument, which is the input file, they will output the RLE encoded representation of the input file to the standard output for debugging purpose (with each count printed as an integer enclosed by square brackets).  

For example, suppose that the content of the input ASCII file called simple.txt is aAAbbbBBBBcccccCCCCCCdDDeeeEEEE

Then > ./rlencode simple.txt
aAAb[0]B[1]c[2]C[3]dDDe[0]E[1]

> ./rlencode simple.txt simple.rle

> ./rldecode simple.rle
aAAb[0]B[1]c[2]C[3]dDDe[0]E[1]


Note that from the example, we observe that rlencode assumes a normal ASCII text file as input and rldecode assumes an RLE-encoded file as input, even though both of them produce the same output. Please also note that to minimize the size of a count, I represent 3 runs as 0 (where 3 is the minimum number used to represent runs using count).  

Use the make command below to compile your solution. A makefile is provided.


The solution is compiled and run on a typical Linux machine e.g. wagner.  Your solution  should not write out any external files other than the index file.   Any solution that writes out external  files other than the index file will receive zero points for the entire assignment. PerformanceYour soluton will not  be tested against any ASCII text files that are larger than 200MB.    In the testing machine, runtime memory is assumed to be always less than 20MB. Runtime memory consumption will be measured by valgrind massif with the option  --pages-as-heap=yes, i.e., all the memory used by your program will be measured.  Any solution that violates this memory requirement will receive zero points for that query test. Any solution that runs for more than 60 seconds on a machine with similar specification  as wagner on a given text file will be killed, and will receive zero points for the tests for that file.
