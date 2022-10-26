//
// Created by sakkammadam on 10/16/22.
//

#ifndef SCRATCHSTUFF_MAPPER_H
#define SCRATCHSTUFF_MAPPER_H

#include <string>
#include <tuple>
#include <vector>
#include <map>

class Mapper {
// Private data members
private:
    std::map<std::string, std::vector<std::vector<std::string>>> processedDirectory;

    //
public:
    // Default Constructor
    Mapper();

    // Initialization Constructor
    explicit Mapper(
            // Get the processed directory object
            const std::map<std::string, std::vector<std::vector<std::string>>> &processed_directory
            );

    // Setters
    // This will set the processedDirectory private data member within the Mapper object
    void setProcessedDirectory(const std::map<std::string, std::vector<std::vector<std::string>>> &processed_directory);

    // Getters
    // This will retrieve the processedDirectory private data member within the Mapper object
    std::map<std::string, std::vector<std::vector<std::string>>> getProcessedDirectory();

    // Cleanup methods -
    // 1) lowerRemovePunc - This method will lowercase and remove punctuations, essentially standardize a line
    // 2) tokenize - This method will tokenize a line and return a vector of tokens - expects a cleaned up line

    // This method will lowercase and remove punctuations - standardize a line
    std::string lowerRemovePunc(const std::string &wholeString);

    // This method will tokenize a line and return a vector of tokens within tuples- expects a standardized line
    // Each tuple will contain token, integer(1), partition# the originating line belonged to
    std::vector<std::tuple<std::string, int, int>> tokenize(const std::string &cleanedUpString, size_t linePartitionNum);

    // Primary Map method
    // It will read a line and tokenize the line into individual words
    // The method will create a vector of tuples from a line
    // Each map will contain a word and the occurrence of that word (1)
    std::vector<std::tuple<std::string, int, int>> mapLine(const std::string &fileLine, size_t partitionNum);

    // Overarching MapOperations method that acts against all lines of a file
    std::map<std::string, std::vector<std::vector<std::vector<std::tuple<std::string, int, int>>>>> mapOperations();

};


#endif //SCRATCHSTUFF_MAPPER_H
