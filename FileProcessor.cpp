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
}

// Initialization constructor - used primarily for shuffler and reducer operations
FileProcessor::FileProcessor(
        const std::string &operation,
        const std::vector<std::map<std::string, std::map<std::string, size_t>>> &shuffle_or_reducer_result
        ) {
    // Set operation - will raise error if the value is incorrect
    this->setOperation(operation);
    if(this->getOperation() == "shuffler"){
        // Set shuffler Data private data member
        this->setShufflerData(shuffle_or_reducer_result);
    } else if (this->getOperation() == "reducer"){
        // Set reducer Data private data member
        this->setReducerData(shuffle_or_reducer_result);
    }

}

// Setter methods
// This will set the FileProcessor's desired operation in private data member directoryOperation
void FileProcessor::setOperation(const std::string &operation) {
    if(operation == "input" || operation == "mapper" || operation == "shuffler" || operation == "reducer"){
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

// This will set the FileProcessor's shuffler data private data member
void FileProcessor::setShufflerData(
        const std::vector<std::map<std::string, std::map<std::string, size_t>>> &shuffle_result) {
    this->shufflerData = shuffle_result;

}

// This will set the FileProcessor's reducer data private data member
void FileProcessor::setReducerData(
        const std::vector<std::map<std::string, std::map<std::string, size_t>>> &reducer_result) {
    this->reducerData = reducer_result;
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

// This will retrieve the shuffler data private data member
std::vector<std::map<std::string, std::map<std::string, size_t>>> FileProcessor::getShufflerData() {
    return this->shufflerData;
}

// This will retrieve the reducer data private data member
std::vector<std::map<std::string, std::map<std::string, size_t>>> FileProcessor::getReducerData() {
    return this->reducerData;
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

// Output operations

// This method will create necessary directory paths
void FileProcessor::createDirectory(const std::string &directoryPath) {
    std::filesystem::path shufflePath(directoryPath);
    if (std::filesystem::exists(directoryPath)) {
        // This should be a log property - @Hal and @Abe - TODO! - should be pushed to log files
        std::cout << "The " << this->getOperation() <<  " directory: " << directoryPath << " already exists! " << std::endl;
    } else {
        // create directory!
        std::filesystem::create_directories(directoryPath);
        // This should be a log property - @Hal and @Abe - TODO! - should be pushed to log files
        std::cout << "Created the " << this->getOperation() << " directory: " << directoryPath << std::endl;
    }
}

// This method will write the outputs of Mapper Operations - it will return the directory of temp_mapper
std::string FileProcessor::writeMapperOutputs() {
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
        this->createDirectory(tempDirectory);
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
}

// This method will write the outputs of Shuffle Operations - it will return the directory of temp_shuffler
std::string FileProcessor::writeShuffleOutputs() {
    // This should be a log property - @Hal and @Abe - TODO! - should be pushed to log files
    std::cout << "Proceeding to write Shuffle data output to file system...." << std::endl;
    // Shuffle data
    std::vector<std::map<std::string, std::map<std::string, size_t>>> shuffleData = this->getShufflerData();
    // Shuffle parent path
    std::string shuffleParentPath;
    // Let's iterate over each map item in the vector
    for(const auto& shufflePartition:shuffleData){
        // let's read corresponding map
        for(const auto &shufflePartitionDetails:shufflePartition){
            // this is the shuffle directory associated
            std::string shuffleDirectory = shufflePartitionDetails.first.substr(0, shufflePartitionDetails.first.rfind('/') + 1);
            // capturing the parent path
            shuffleParentPath = std::filesystem::path(shuffleDirectory).parent_path().parent_path().string();
            // We need to check if directory exists. if it doesn't - create the directory, else don't do anything
            // Creating shuffle directory if shuffle directory is not there already
            this->createDirectory(shuffleDirectory);
            // @Hal, @Abraham - please log this! TODO! - should be pushed to log files
            std::cout << "Proceeding to create " << shufflePartitionDetails.first << std::endl;
            // declare an ostream
            std::ofstream outputFile;
            // create an empty file against the temp directory
            outputFile.open(shufflePartitionDetails.first);
            // let's iterate over the map
            for(const auto &tokenDetails:shufflePartitionDetails.second){
                std::string prepRow = "(" + tokenDetails.first + "," + std::to_string(tokenDetails.second) + ")";
                outputFile << prepRow << std::endl;
            }
            // close the output file
            outputFile.close();
        }
    }
    // return shuffleParentPath
    return shuffleParentPath;
}


// This method will write the outputs of Reducer Operations - it will return the directory of final_output
std::string FileProcessor::writeReduceOutputs() {
    // This should be a log property - @Hal and @Abe - TODO! - should be pushed to log files
    std::cout << "Proceeding to write reducer data output to file system...." << std::endl;
    // Reducer data
    std::vector<std::map<std::string, std::map<std::string, size_t>>> reduceData = this->getReducerData();
    // Shuffle parent path
    std::string reducerParentPath;
    // Let's iterate over each map item in the vector
    for(const auto& reduceFileDirData:reduceData) {
        // let's read corresponding map
        for (const auto &reduceFile: reduceFileDirData) {
            // this is the shuffle directory associated
            std::string reduceFileDir = reduceFile.first.substr(0, reduceFile.first.rfind('/') + 1);
            // capturing the grandparent path
            reducerParentPath = std::filesystem::path(reduceFileDir).parent_path().string();
            // We need to check if directory exists. if it doesn't - create the directory, else don't do anything
            // Creating shuffle directory if shuffle directory is not there already
            this->createDirectory(reduceFileDir);
            // @Hal, @Abraham - please log this! TODO! - should be pushed to log files
            std::cout << "Proceeding to create " << reduceFile.first << std::endl;
            // declare an ostream
            std::ofstream outputFile;
            // create an empty file against the temp directory
            outputFile.open(reduceFile.first);
            // let's iterate over the map
            for (const auto &tokenDetails: reduceFile.second) {
                std::string prepRow = "(" + tokenDetails.first + "," + std::to_string(tokenDetails.second) + ")";
                outputFile << prepRow << std::endl;
            }
            // close the output file
            outputFile.close();
        }
    }
    // return the grandparent path
    return reducerParentPath;
}

// This method will write corresponding data points to disk
// It will return the directory name where data is being written to.
std::string FileProcessor::writeDirectory() {
    std::string tempDirectoryCreated;
    // Mapper operation support
    if (this->getOperation() == "mapper") {
        tempDirectoryCreated = this->writeMapperOutputs();
        return tempDirectoryCreated;
    } else if(this->getOperation() == "shuffler"){
        tempDirectoryCreated = this->writeShuffleOutputs();
        return tempDirectoryCreated;
    } else if(this->getOperation() == "reducer"){
        // to implement!
        tempDirectoryCreated = this->writeReduceOutputs();
        return tempDirectoryCreated;
    } else {
        // no other cases to cover
        throw std::runtime_error("Unsupported operation!: " + this->getOperation() );
    }
}