//
// Created by sakkammadam on 10/22/22.
//

#include "Reducer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <map>
#include <vector>

// Default Constructor
Reducer::Reducer() {
    // Nothing here! - we will be using explicit versions of constructor for the most part!
}

// Explicit Constructor that will take the shuffle directory as input
Reducer::Reducer(const std::string &parent_shuffle_directory) {
    // Set the private data member mapShuffleDirectory here
    this->setShuffleOutputDirectory(parent_shuffle_directory);
}

// Setters
// This method sets the mapShuffleDirectory private data member
void Reducer::setShuffleOutputDirectory(const std::string &parent_shuffle_directory) {
    // Check if the shuffle directory exists on the file system
    std::filesystem::path directoryPath(parent_shuffle_directory);
    if(std::filesystem::is_directory(directoryPath)){
        this->parentShuffleDirectory = parent_shuffle_directory;
    } else {
        throw std::runtime_error("Directory not found!: " + parent_shuffle_directory );
    }
}

// Getters
// This method retrieves the mapShuffleDirectory private data member
std::string Reducer::getShuffleOutputDirectory() {
    return this->parentShuffleDirectory;
}

// Primary operations!

// This method will process a single shuffle file directory path and produce an object in memory
// The memory object is a map of the directory (fileName) and its value is another map
// that contains all tokens across all partitions and their total counts
std::map<std::string, std::map<std::string, size_t>> Reducer::reduceFile(
        const std::string &fullyQualifiedShuffleFilePath) {
    // Declare the reduced file object
    std::map<std::string, std::map<std::string, size_t>> singleReducedFile;
    // Check if the file directory is present in the file system
    std::filesystem::path directoryPath(fullyQualifiedShuffleFilePath);
    // Do the following only if the directory exists in the file system!
    if (std::filesystem::is_directory(directoryPath)) {
        std::cout << "Reducing directory path - " << fullyQualifiedShuffleFilePath << std::endl;
        // Create temp objects
        std::map<std::string, size_t> tempReduce;
        for (const auto &entry: std::filesystem::directory_iterator(fullyQualifiedShuffleFilePath)) {
            // Checking if the underlying path is a file
            if (std::filesystem::is_regular_file(entry.path())) {
                // if it's a file - push it into vector
                // Read the file as an input stream
                std::ifstream inputFile(entry.path().string());
                // Declare a string for each line in the file
                std::string fileLine;
                // parse the file line by line
                while (std::getline(inputFile, fileLine)) {
                    // Capturing the token using substr - it will extract from 2nd position upto the comma occurrence
                    std::string token = fileLine.substr(1, fileLine.find(',') - 1);
                    // Capturing the occurrence using substr - it will extract from the comma to closing parentheses
                    // We use stoi to convert to integer
                    size_t tokenOccurrence = std::stoi(fileLine.substr(
                            fileLine.find(',') + 1, (fileLine.find(')') - fileLine.find(',')) - 1));
                    // Now will check if the token exists in tempReduce
                    // Let's create an iterator that will check tempShuffle for the token
                    auto mapItr = tempReduce.find(token);
                    // Check if iterator was exhausted
                    if (mapItr == tempReduce.end()) {
                        // if parsedToken was not found! - lets insert into tempShuffle
                        tempReduce.insert({token, tokenOccurrence});
                    } else {
                        // token was found! - let's increment the existing value with the token's current occurrence (within a partition file)
                        mapItr->second = (mapItr->second) + tokenOccurrence;
                    }
                }
            }
        }
        // at this point, tempShuffle has the complete token counts of a partition file
        // lets create a new fully qualified path where we will replace "/temp_shuffler/" with "/final_output/"
        std::string fullyQualifiedOutFilePath = fullyQualifiedShuffleFilePath;
        // the string we are trying to replace
        std::string toReplace("/temp_shuffler/");
        // find its position within the file path
        size_t pos = fullyQualifiedOutFilePath.find(toReplace);
        // lets replace
        fullyQualifiedOutFilePath.replace(pos, toReplace.length(), "/final_output/");
        // we will simply attach it to the desired output file and save the result to singleReducedFile object
        singleReducedFile.insert({fullyQualifiedOutFilePath, tempReduce});
    } else {
        std::cout << "** Warning! ** Shuffle directory: " << fullyQualifiedShuffleFilePath << "doesn't exist in the file system!" << std::endl;
    }
    // final return
    return singleReducedFile;
}


// This method will operate against each processed partition file within the shuffle directory
std::vector<std::map<std::string, std::map<std::string, size_t>>> Reducer::reduceOperations() {
    // Declare an empty vector that will contain reduced file (filename) and token data and counts, as maps
    std::vector<std::map<std::string, std::map<std::string, size_t>>> directoryReduceVector;
    // Let's create a vector that will hold all the directories within the temp_shuffler
    std::vector<std::string> shufflerDirectoryFiles;
    // Let's iterate over the temp_shuffler path
    for(const auto &entry: std::filesystem::directory_iterator(this->getShuffleOutputDirectory())){
        // Checking if the recursive path was a directory
        if(std::filesystem::is_directory(entry.path())){
            // if it's a directory - push it into vector
            shufflerDirectoryFiles.push_back(entry.path());
        }
    }
    // if there are files, we will iterate over each fileDirectory path
    if(!shufflerDirectoryFiles.empty()) {
        // Let's iterate over each subdirectory named after a file
        for (const auto &dirShuffleFile: shufflerDirectoryFiles) {
            // Let's iterate over each shuffled file within the directory
            std::map<std::string, std::map<std::string, size_t>> reducedDir = this->reduceFile(dirShuffleFile);
            directoryReduceVector.push_back(reducedDir);
        }
    } else {
        std::cout << "**Warning** Shuffle directory path " << this->getShuffleOutputDirectory() << " is empty!" << std::endl;
    }
    // return object for downstream processing
    return directoryReduceVector;
}