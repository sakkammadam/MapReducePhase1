//
// Created by sakkammadam on 10/13/22.
//

#include "FileProcessor.h"
#include <iostream>
#include <cmath>
#include <string>
#include <filesystem>
#include <fstream>


// Default Constructor
FileProcessor::FileProcessor():directoryOperation{" "},directoryPath{" "} {
    // Nothing in the body of the default constructor
    // Note that we have set the private data members as blank!
}

// Primary Constructor
FileProcessor::FileProcessor(const std::string &operation, const std::string &directory_path) {
    // Set Operation - will raise error if the value is incorrect
    setOperation(operation);
    // Set Directory path - will raise error if the path is not present in the file system
    setDirectoryPath(directory_path);
    // Entry method - to be added
}

void FileProcessor::setOperation(const std::string &operation) {
    if(operation == "input" || operation == "output"){
        this->directoryOperation = operation;
    } else{
        throw std::runtime_error("Unsupported operation!: " + operation );
    }
}

void FileProcessor::setDirectoryPath(const std::string &directory_path) {
    std::filesystem::path p(directory_path);
    if(std::filesystem::exists(p)){
        this->directoryPath = directory_path;
    } else {
        throw std::runtime_error("Directory not found!: " + directory_path );
    }
}

std::string FileProcessor::getOperation() {
    return this->directoryOperation;
}

std::string FileProcessor::getDirectoryPath() {
    return this->directoryPath;
}

int FileProcessor::linesPerFile(const std::string &fileName) {
    // Read the file as an input stream
    std::ifstream inputFile(fileName);
    // Initialize the total lines per file
    int numLines = 0;
    // declare a line variable
    std::string line;
    // Read the input file and find the total number of lines
    while(std::getline(inputFile, line)){
        ++numLines;
    }
    // Simple analysis
    std::cout << "The file " << fileName << " has " << numLines << " lines." << std::endl;
    return numLines;
}

std::map<std::string, std::vector<std::vector<std::string>>> FileProcessor::readDirectory() {
    // Declare an empty map that will contain filenames and their corresponding file data as partitions
    std::map<std::string, std::vector<std::vector<std::string>>> directoryData;
    // Let's create a vector that holds the filenames within the directory
    std::vector<std::string> directoryFiles;
    // let's set up the directory path
    std::string filePath = this->getDirectoryPath();
    // let's find the files
    for(const auto &entry: std::filesystem::directory_iterator(filePath)){
        std::cout << entry.path() << std::endl;
        directoryFiles.push_back(entry.path());
    }
    // if there are no files -
    if(!directoryFiles.empty()){
        // let's iterate each file!
        for(auto i=0; i < directoryFiles.size(); i++){
            // Declare a vector of vectors that contain strings - this is unique per file!
            std::vector<std::vector<std::string>> vecFile;
            // Read the file as an input stream
            std::ifstream inputFile(directoryFiles[i]);
            // Create a reference variable against the file name
            std::string &refFile = directoryFiles[i];
            // Declare a string for each line in the file
            std::string fileLine;
            // Find the number of lines per file
            int numLinesPerFile = linesPerFile(refFile);
            // Set the number of lines per partition
            int numLinesPerPartition = 500;
            // Determine number of partitions per file
            int numPartitionsPerFile = ceil(numLinesPerFile/double(numLinesPerPartition));
            // This should be a log property - @Hal and @Abe - TODO! - should be pushed to log files
            std::cout << "Properties for " << refFile << std::endl;
            std::cout << "Number of lines: " << numLinesPerFile << std::endl;
            std::cout << "Number of lines per partition: " << numLinesPerPartition << std::endl;
            std::cout << "NUmber of partitions per file: " << numPartitionsPerFile << std::endl;
            // TO DO - the above 4 lines should be pushed to log
            // Represent the current line number
            int currentLine = 0;
            // Initialize partition
            int partition = 1;
            // Preemptively declare a vector of strings
            std::vector<std::string> simpleVec;
            // Parse the file line by line!
            while(std::getline(inputFile, fileLine)){
                // push each line into the vector of strings
                simpleVec.push_back(fileLine);
                // increment the currentLine variable
                ++currentLine;
                // if the lines falls outside the partition, then we need to push it to a new partition!
                if(currentLine >= (partition) * numLinesPerPartition && partition < numPartitionsPerFile){
                    // increase the partition count
                    ++partition;
                    // push it to ioFiles (the vector of string vectors)
                    vecFile.push_back(simpleVec);
                    // clear the simple vector so that we can start covering for the next partition!
                    simpleVec.clear();
                } else if (currentLine == numLinesPerFile && partition == numPartitionsPerFile){
                    // this is to cover for the last partition!
                    // push it to ioFiles (the vector of string vectors)
                    vecFile.push_back(simpleVec);
                } else {
                    // do nothing for all other lines
                }
            }
            // Insert into map - this contains all data broken down in partitions (lines) for one file!
            directoryData.insert({directoryFiles[i], vecFile});
        }
    } else {
        std::cout << "**Warning** directory path "<<  this->getDirectoryPath() << " is empty!" << std::endl;
    }
    // Send final output
    return directoryData;
}

// Not set up yet!
void FileProcessor::writeDirectory() {
    // Will pick this up after mapper class
}

// Not set up yet!
void FileProcessor::entryMethod() {
    // Will pick this up after mapper class
}








