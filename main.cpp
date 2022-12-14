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

// Overarching function that will orchestrate the main flow
void runOperations(const std::string &input_directory);

// Overarching function that will perform Map reduce operations
void mapReduceWorkflow(const std::string &input_directory);

int main(int argc, char* argv[]) {

    // Check arguments supplied
    if(argc==1){
        // No arguments were provided!
        std::cout << "No arguments were provided! Please resubmit with input paths!" << std::endl;
    } else {
        // Declare the file being processed
        char* inputDirBase = argv[1];
        // convert to string
        std::string inputDir(inputDirBase);
        // Orchestrate the entire operation
        try{
            runOperations(inputDir);
        }
        catch (std::runtime_error &runtime_error){
            std::cout << "Exception occurred: " << runtime_error.what() << std::endl;
        }
    }

    // standard return
    return 0;
}

// Overarching function that will orchestrate the main flow
void runOperations(const std::string &input_directory){
    // Let's check if the input directory exists in the file system
    std::filesystem::path directoryPath(input_directory);
    if(std::filesystem::is_directory(directoryPath)){
        // Let's declare a vector to hold filenames within input directory
        std::vector<std::string> directoryInputFiles;
        // let's find the files
        for(const auto &entry: std::filesystem::directory_iterator(input_directory)){
            directoryInputFiles.push_back(entry.path());
        }
        if(!directoryInputFiles.empty()){
            // Call mapReduceOperations function here!
            std::cout << "Kicking off MapReduce operations..." << std::endl;
            mapReduceWorkflow(input_directory);
        } else {
            std::cout << "No files found to process along " << input_directory << std::endl;
        }

    } else {
        throw std::runtime_error("Directory not found!: " + input_directory );
    }
}

// file Directory checks
std::vector<std::string> fileDirectoryChecks(const std::string &directory1, const std::string &directory2){
    // Map containing input files in directory1
    std::map<std::string, int> dir1MapFiles;
    // Vector containing files that don't exist
    std::vector<std::string> filesDontExist;
    // let's iterate over the directory1
    for(const auto &entry: std::filesystem::directory_iterator(directory1)){
        if(std::filesystem::is_regular_file(entry)){
            std::string fileDirectory = entry.path().string().substr(0, entry.path().string().rfind('/') + 1);
            std::string baseFileName = entry.path().string().substr(entry.path().string().rfind('/') + 1);
            dir1MapFiles.insert({baseFileName,1});
        }
    }
    // check if directory2 is present ...
    // Let's check if that output directory is there!
    if(!std::filesystem::is_directory(directory2)){
        throw std::runtime_error("Output Directory not found!: " + directory2 );
    } else {
        // continue
        for(const auto &entry: std::filesystem::directory_iterator(directory2)){
            if(std::filesystem::is_regular_file(entry)){
                std::string fileDirectory = entry.path().string().substr(0, entry.path().string().rfind('/') + 1);
                std::string baseFileName = entry.path().string().substr(entry.path().string().rfind('/') + 1);
                // Let's create an iterator that will check tempShuffle for the token
                auto mapItr = dir1MapFiles.find(baseFileName);
                // Check if iterator was exhausted
                if (mapItr == dir1MapFiles.end()) {
                    // if parsedToken was not found! - lets create a entry in filesDontExist vector
                    filesDontExist.push_back(baseFileName);
                }
            }
        }
    }
    // return filesDontExist vector
    return filesDontExist;
}

// Overarching function that will perform Map reduce operations
void mapReduceWorkflow(const std::string &input_directory){
    // Creating an object using FileProcessor
    // We are using the explicit CTOR defined for input operations
    FileProcessor allInputData("input",input_directory);

    // Retrieve private data members - directory and requested operation (input)
    std::cout << allInputData.getInputDirectoryPath() << std::endl;
    std::cout << allInputData.getOperation() << std::endl;
    // Create a map of 2d vectors that will host all data present along the path
    std::map<std::string, std::vector<std::vector<std::string>>> directoryData = allInputData.readDirectory();

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

    std::cout << "Output of Mapper operations have been written to " << mapDirectory << std::endl;

    // Create a Shuffle object whose input is the map of 3d vectors - output of Mapper operations viz. partitioned files
    Shuffler shuffleRun(mapDirectory);
    // Create a vector of map of maps that will host tokens and their counts across all partitions
    std::vector<std::map<std::string, std::map<std::string,size_t>>> shuffledData;
    shuffledData = shuffleRun.shuffleOperations();

    // let's provide result of shuffle to FileProcessor to write them to disk
    FileProcessor shuffleOutputToDisk("shuffler",shuffledData);
    std::string shuffleDirectory = shuffleOutputToDisk.writeDirectory();

    std::cout << "Output of shuffle operations have been written to " << shuffleDirectory << std::endl;

    // let's provide the shuffle directory to the Reducer !
    Reducer reduceRun(shuffleDirectory);
    std::vector<std::map<std::string, std::map<std::string,size_t>>> reducedData;
    reducedData = reduceRun.reduceOperations();

    // lets provider result of reducer to FileProcessor to write them to disk
    FileProcessor reduceOutputToDisk("reducer",reducedData);
    std::string outputDirectory = reduceOutputToDisk.writeDirectory();

    std::cout << "Output data has been written to " << outputDirectory << std::endl;

    std::vector<std::string> fileDontExist1to2 = fileDirectoryChecks(input_directory, outputDirectory);
    std::vector<std::string> fileDontExist2to1 = fileDirectoryChecks(outputDirectory, input_directory);

// Create a SUCCESS indicator if filesDontExist vector is empty
    if(fileDontExist1to2.empty() && fileDontExist2to1.empty()){
        std::ofstream successFile;
        successFile.open(outputDirectory + "/" + "SUCCESS.ind");
        successFile.close();
    } else {
        throw std::runtime_error("There are missing files!");
    }
}