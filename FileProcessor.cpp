//
// Created by sakkammadam on 10/13/22.
//

#include "FileProcessor.h"
#include<iostream>
#include<math.h>
#include<string>
#include<filesystem>
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

            std::string &refFile = directoryFiles[i];

            // Declare a string for each line in the file
            std::string fileLine;

            // Find the number of lines per file
            int numLinesPerFile = linesPerFile(refFile);

            // Determine number of lines per partition
            int numLinesPerPartition = 500;

            // Determine number of partitions per file
            int numPartitionsPerFile = ceil(numLinesPerFile/double(numLinesPerPartition));

            std::cout << "Properties for " << refFile << std::endl;;
            std::cout << "Number of lines: " << numLinesPerFile << std::endl;
            std::cout << "Number of lines per partition: " << numLinesPerPartition << std::endl;
            std::cout << "NUmber of partitions per file: " << numPartitionsPerFile << std::endl;

            // Represent the current line number
            int currentLine = 0;

            // Initialize partition
            int partition = 1;

            // Preemptively declare a vector of strings
            std::vector<std::string> simpleVec;

            // Parse the file -
            while(std::getline(inputFile, fileLine)){
                // push each line into the vector of strings
                simpleVec.push_back(fileLine);
                // increment the currentLine variable
                ++currentLine;
                // if the lines falls outside the partition, then we need to push it to a new partition!
                // @Hal / @Abraham - there is a bug here ?
                //std::cout << "(partition:"<< partition <<")," << "(currentLine:" << currentLine <<")" << std::endl;
                if(currentLine >= (partition) * numLinesPerPartition && partition < numPartitionsPerFile){
                    //std::cout << "Within the IF block" << std::endl;
                    //std::cout << "(partition:"<< partition <<")," << "(currentLine:" << currentLine <<")" << std::endl;
                    // increase the partition count
                    ++partition;
                    //std::cout << "(increased partition:"<< partition <<")" << std::endl;
                    // push it to ioFiles (the vector of string vectors)
                    vecFile.push_back(simpleVec);
                    // recreate the simple vector
                    simpleVec.clear();
                } else if (currentLine == numLinesPerFile && partition == numPartitionsPerFile){
                    // std::cout << "Will it come here ?" << std::endl;
                    // this is the last partition!
                    // push it to ioFiles (the vector of string vectors)
                    vecFile.push_back(simpleVec);
                } else {
                    // do nothing for all other lines
                }
            }
            // Insert into map - this contains all data for that one file!
            directoryData.insert({directoryFiles[i], vecFile});
        }
    } else {
        std::cout << "**Warning** directory path "<<  this->getDirectoryPath() << " is empty!" << std::endl;
    }
    // Send final output
    return directoryData;
}








