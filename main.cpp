#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <tuple>
#include <vector>
#include <filesystem>
#include "FileProcessor.h"
#include "Mapper.h"
#include "Shuffler.h"
#include "Reducer.h"

int main(int argc, char* argv[]) {
    // Declare the file being processed
    //char* filePathBase = argv[1];
    //std::string filePath(filePathBase);


    // Create a testing object called testingFoo -- the directory path should be filePath - line #13
    FileProcessor testSample(
            "input",
            "/home/sakkammadam/Documents/syr/cse687/projects/input_files/sample"
            );

    // Retrieve private data members - directory and requested operation (input)
    std::cout << testSample.getInputDirectoryPath() << std::endl;
    std::cout << testSample.getOperation() << std::endl;
    // Create a map of 2d vectors that will host all data present along the path
    std::map<std::string, std::vector<std::vector<std::string>>> directoryData = testSample.readDirectory();

    // declare a map of 3d vector objects that will hold the results of mapper operations
    std::map<std::string, std::vector<std::vector<std::vector<std::tuple<std::string, int, int>>>>> mappedData;

    // Create a Mapper object whose input is the 2d vector representation of all data along the input directory path
    Mapper mapRun(directoryData);
    // Loaded results of map operations in memory to peek variable
    mappedData = mapRun.mapOperations();

    // Create a File Processor object that will write output of Mapper class to disk
    FileProcessor mapperOutputToDisk("mapper",mappedData);
    // Proceed to write data to disk, capture the directory path and assign to mapDirectory
    std::string mapDirectory = mapperOutputToDisk.writeDirectory();

    // Please log this - @Hal, @Abraham - TODO
    std::cout << "Output of Mapper operations have been written to " << mapDirectory << std::endl;

    // Create a Shuffle object whose input is the map of 3d vectors - output of Mapper operations viz. partitioned files
    Shuffler shuffleRun(mapDirectory);
    // Create a vector of map of maps that will host tokens and their counts across all partitions
    std::vector<std::map<std::string, std::map<std::string,size_t>>> shuffledData;
    shuffledData = shuffleRun.shuffleOperations();

    // let's provide result of shuffle to FileProcessor to write them to disk
    FileProcessor shuffleOutputToDisk("shuffler",shuffledData);
    std::string shuffleDirectory = shuffleOutputToDisk.writeDirectory();

    // Please log this - @Hal, @Abraham - TODO
    std::cout << "Output of shuffle operations have been written to " << shuffleDirectory << std::endl;

    // let's provide the shuffle directory to the Reducer !
    Reducer reduceRun(shuffleDirectory);
    std::vector<std::map<std::string, std::map<std::string,size_t>>> reducedData;
    reducedData = reduceRun.reduceOperations();

    // lets provider result of reducer to FileProcessor to write them to disk
    FileProcessor reduceOutputToDisk("reducer",reducedData);
    std::string outputDirectory = reduceOutputToDisk.writeDirectory();

    // Please log this - @Hal, @Abraham - TODO
    std::cout << "Output data has been written to " << outputDirectory << std::endl;

    return 0;
}
