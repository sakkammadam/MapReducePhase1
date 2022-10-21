//
// Created by sakkammadam on 10/20/22.
//

#ifndef SCRATCHSTUFF_SHUFFLER_H
#define SCRATCHSTUFF_SHUFFLER_H

#include <iostream>
#include <filesystem>
#include <string>
#include <map>
#include <vector>
#include <regex>

class Shuffler {
private:
    // Private data member - directory containing mapper outputs
    std::string mapOutputDirectory;

public:
    // default constructor
    Shuffler();

    // explicit constructor
    explicit Shuffler(const std::string &mapper_directory);

    // Setters
    // This method sets the mapOutputDirectory private data member
    void setMapOutputDirectory(const std::string &mapper_directory);

    // Getters
    // This method retrieves the mapOutputDirectory private data member
    std::string getMapOutputDirectory();

    // Primary Operations

    // This method will process a single partitioned Mapper file and produce an object in memory
    // The memory object is a map of the file (key) and its value is another that contains tokens
    // and their count within that partitioned file
    std::map<std::string, std::map<std::string,size_t>> shuffleFile(const std::string &fullyQualifiedFile);

    // Overarching method that will read subdirectories and associated partitioned files within temp_mapper directory
    // For each partition file within the file subdirectory, the shuffleFile method will be called
    std::vector<std::map<std::string, std::map<std::string,size_t>>> shuffleOperations();

};


#endif //SCRATCHSTUFF_SHUFFLER_H
