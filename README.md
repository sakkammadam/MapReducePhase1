# MapReducePhase1
MapReduce - CSE687 project - phase#1

# Background
In Phase 1, we will be writing a standalone command-line program that can run a word count MapReduce workflow. Runs as a single process, no threads or multiple processes (yet). The program will take an input directory where text files are stored and will ultimately produce a single output file that contains a list of words and their associated counts in the originating input files. 


# Understanding the code

1.  Code logic conducts appropriate input error-checking and exception-handling, which will not be discussed except in response to audience questions.
2.  Pass command-line input (input_directory) to FileProcessor object (allInputData).
3.  Create a map of two-dimensional vectors (directoryData) to host all data found in the input_directory.
4.  Execute readDirectory() member function to read all data in input_directory into directoryData.

![](https://github.com/sakkammadam/MapReducePhase1/blob/development/classes_and_seq_diagram/Fileprocessor.jpg)

5.  Create a Mapper object (mapRun) that takes directoryData as an input, conducts mapOperations (removes punctuation and white space), lowercases and tokenizes data(mappedData).
6.  Create a FileProcessor object (mapperOutputToDisk) to write mappedData to disk(Format e.g., (“a”, 1), (”the”, 1)…).

![](https://github.com/sakkammadam/MapReducePhase1/blob/development/classes_and_seq_diagram/Mapper.jpg) 

7.  Create a Shuffler object (shuffleRun) that takes mapDirectory as an input.
8.  Create a vector of map of maps to host tokens and corresponding counts written to disk previously (shuffledData).
9.  Read data from mapDirectory into shuffledData and sort data partition by partition.
10. Create a FileProcessor object (shuffleOutputToDisk) to write shuffledData to disk(Format e.g., (“a”, 7), (”the”, 16)… partition by partition). 

![](https://github.com/sakkammadam/MapReducePhase1/blob/development/classes_and_seq_diagram/Shuffler.jpg) 

11. Create a Reducer object (reduceRun) that takes shuffleDirectory as an input.
12. Create a vector of map of maps to host tokens and corresponding counts written to disk previously (reducedData).
13. Read data from shuffleDirectory into shuffledData and sort data into final form.
14. Create a FileProcessor object (reduceOutputToDisk) to write reducedData to disk(Format e.g., (“a”, 257), (”the”, 316)… all results aggregated into one output file per input file). 

![](https://github.com/sakkammadam/MapReducePhase1/blob/development/classes_and_seq_diagram/Reducer.jpg)

# Sequence Diagram

![](https://github.com/sakkammadam/MapReducePhase1/blob/development/classes_and_seq_diagram/mapReduceSequenceDiagram.png)

# Running the code instructions

Looking to run the code on your machine?

You must run this command line for

Ubuntu: 
g++ --std=c++17 main.cpp FileProcessor.cpp FileProcessor.h Mapper.h Mapper.cpp Shuffler.cpp Shuffler.h Reducer.cpp Reducer.h -o mapReducePhase1

Mac: 
g++ --std=c++17 main.cpp FileProcessor.cpp Mapper.cpp Shuffler.cpp Shuffler.h Reducer.cpp Reducer.h -o mapReducePhase1

then lastly inout to the command line:
./mapReducePhase1 <InputDirectory> > logs/run_`date '+%Y%m%d%H%M%S'`.log

