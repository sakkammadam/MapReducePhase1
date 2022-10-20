//
// Created by sakkammadam on 10/13/22.
//

#include "FileProcessor.h"
#include <iostream>
#include <cmath>
#include <string>
#include <filesystem>
#include <fstream>
#include <map>
#include <vector>
#include <tuple>


// Default Constructor
FileProcessor::FileProcessor(): directoryOperation{" "}, inputDirectoryPath{" "} {
    // Nothing in the body of the default constructor
    // Note that we have set the private data members as blank!
}

// Constructor used primarily for input operations
FileProcessor::FileProcessor(const std::string &operation, const std::string &directory_path) {
    // Set Operation - will raise error if the value is incorrect
    this->setOperation(operation);
    // Set Directory path - will raise error if the path is not present in the file system
    this->setInputDirectoryPath(directory_path);
    // Entry method - to be added - the entry method in this CTOR should fall into the input path!
}

// Constructor used in conjunction with mapper operations
// Initialization constructor - used primarily for mapper operations
FileProcessor::FileProcessor(
        const std::string &operation,
        const std::map<std::string, std::vector<std::vector<std::vector<std::tuple<std::string, int, int>>>>> &map_result
        ) {
    // Set operation - will raise error if the value is incorrect
    this->setOperation(operation);
    // Set mapper Data private data member
    this->setMapperData(map_result);
    // Entry method - to be added - the entry method for this CTOR should fall into the mapper path!
}

// Setter methods
// This will set the FileProcessor's desired operation in private data member directoryOperation
void FileProcessor::setOperation(const std::string &operation) {
    if(operation == "input" || operation == "mapper" || operation == "sorter" || operation == "output"){
        this->directoryOperation = operation;
    } else{
        throw std::runtime_error("Unsupported operation!: " + operation );
    }
}

// This will set the FileProcessor's directory path that contain files in private data member inputDirectoryPath
void FileProcessor::setInputDirectoryPath(const std::string &directory_path) {
    std::filesystem::path p(directory_path);
    if(std::filesystem::exists(p)){
        this->inputDirectoryPath = directory_path;
    } else {
        throw std::runtime_error("Directory not found!: " + directory_path );
    }
}

// This will set the FileProcessor's mapper Data private data member
void FileProcessor::setMapperData( const std::map<std::string, std::vector<std::vector<std::vector<std::tuple<std::string, int, int>>>>> &map_result) {
    this->mapperData = map_result;
}

// Getter methods
// This will retrieve the private data member directoryOperation
std::string FileProcessor::getOperation() {
    return this->directoryOperation;
}

// This will retrieve the private data member inputDirectoryPath
std::string FileProcessor::getInputDirectoryPath() {
    return this->inputDirectoryPath;
}

// This will retrieve the mapper data private data member
std::map<std::string, std::vector<std::vector<std::vector<std::tuple<std::string, int, int>>>>> FileProcessor::getMapperData() {
    return this->mapperData;
}

// This method will determine the number of lines per file used in conjunction with readDirectory method
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

//  primary input operations - this method will crate a map containing vector of vectors
std::map<std::string, std::vector<std::vector<std::string>>> FileProcessor::readDirectory() {
    // Declare an empty map that will contain filenames and their corresponding file data as partitions
    std::map<std::string, std::vector<std::vector<std::string>>> directoryData;
    // Let's create a vector that holds the filenames within the directory
    std::vector<std::string> directoryFiles;
    // let's set up the directory path
    std::string filePath = this->getInputDirectoryPath();
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
            // TODO - the above 4 lines should be pushed to log
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
        std::cout << "**Warning** directory path " << this->getInputDirectoryPath() << " is empty!" << std::endl;
    }
    // Send final output
    return directoryData;
}

// This method will write corresponding data points to disk
// It will return the directory name where data is being written to.
std::string FileProcessor::writeDirectory() {
    // Mapper operation support
    if (this->getOperation() == "mapper") {
        // This should be a log property - @Hal and @Abe - TODO! - should be pushed to log files
        std::cout << "Proceeding to write Mapper data output to file system...." << std::endl;
        // Declare variable mapData
        // Key -> FileName
        // Value -> Vector containing tuples -> (Token, 1, Originating Partition the token (line belonged to)
        std::map<std::string, std::vector<std::vector<std::vector<std::tuple<std::string, int, int>>>>> mapData = this->getMapperData();
        // Declare tempDirectory
        std::string rootTempDirectory;
        // We will be iterating over the mapData map
        for (const auto &itr: mapData) {
            std::string fullyQualifiedFileName = itr.first;
            std::string fileDirectory = fullyQualifiedFileName.substr(0, fullyQualifiedFileName.rfind('/') + 1);
            rootTempDirectory = fileDirectory + "temp_mapper/";
            std::string baseFileName = fullyQualifiedFileName.substr(fullyQualifiedFileName.rfind('/') + 1);
            std::string tempDirectory = rootTempDirectory + baseFileName + "/";
                    // This should be a log property - @Hal and @Abe - TODO! - should be pushed to log files
            std::cout << "Operating on Mapper output from " << fullyQualifiedFileName << std::endl;
            std::cout << "Originating directory: " << fileDirectory << std::endl;
            std::cout << "Creating a temp directory to host mapper output: " << tempDirectory << std::endl;
            // The above three lines should be logged
            // Creating temp directory if temp directory is not there already
            std::filesystem::path tempPath(tempDirectory);
            if (std::filesystem::exists(tempPath)) {
                // This should be a log property - @Hal and @Abe - TODO! - should be pushed to log files
                std::cout << "The temp directory: " << tempDirectory << " already exists! " << std::endl;
            } else {
                // create directory!
                std::filesystem::create_directories(tempDirectory);
                // This should be a log property - @Hal and @Abe - TODO! - should be pushed to log files
                std::cout << "Created the temp directory: " << tempDirectory << std::endl;
            }
            // Let's iterate over the entire mapper data going against each partition
            for (size_t partition = 0; partition < itr.second.size(); ++partition) {
                // we will process all data within partition vector by writing to a file
                // declare an ostream
                std::ofstream outputFile;
                // create an empty file against the temp directory
                outputFile.open(tempDirectory + baseFileName + "." + std::to_string(partition));
                // iterate over each partition vector
                for (const auto &segment: itr.second[partition]) {
                    //outputFile << std::get<0>(itr.second[partition]) << std::endl;
                    for (const auto &token: segment) {
                        std::string prepRow = '(' +
                                std::get<0>(token) + ',' +
                                        std::to_string((char) std::get<1>(token)) + ')';
                        outputFile << prepRow << std::endl;
                    }
                }
                // close the output file
                outputFile.close();
            }
        }
        // return the root temp directory
        return rootTempDirectory;
    } else if(this->getOperation() == "sorter"){
        // to implement!
        return "foo";
    } else if(this->getOperation() == "output"){
        // to implement!
        return "bar";
    } else {
        // no other cases to cover
        return "Nothing";
    }
}

// Not set up yet!
void FileProcessor::entryMethod() {
    // Will pick this up after mapper class
}
