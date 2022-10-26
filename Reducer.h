//
// Created by sakkammadam on 10/22/22.
//

#ifndef SCRATCHSTUFF_REDUCER_H
#define SCRATCHSTUFF_REDUCER_H
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <map>
#include <vector>

class Reducer {
private:
    // Private data member - directory containing shuffler outputs
    std::string parentShuffleDirectory;

public:
    // Default constructor
    Reducer();

    // explicit constructor
    explicit Reducer(const std::string &parent_shuffle_directory);

    // Setters
    // This method sets the mapShuffleDirectory private data member
    void setShuffleOutputDirectory(const std::string &parent_shuffle_directory);

    // Getters
    // This method retrieves the mapShuffleDirectory private data member
    std::string getShuffleOutputDirectory();

    // Primary operations!

    // This method will process a single shuffle file directory path and produce an object in memory
    // The memory object is a map of the directory (fileName) and its value is another map
    // that contains all tokens across all partitions and their total counts
    std::map<std::string, std::map<std::string,size_t>> reduceFile(const std::string &fullyQualifiedShuffleFilePath);

    // This method will operate against each processed partition file within the shuffle directory
    std::vector<std::map<std::string, std::map<std::string, size_t>>> reduceOperations();
};


#endif //SCRATCHSTUFF_REDUCER_H
