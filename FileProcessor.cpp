//
// Created by sakkammadam on 10/13/22.
//

#include "FileProcessor.h"
#include<string>
#include<filesystem>



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






