//
// Created by sakkammadam on 10/16/22.
//

#ifndef SCRATCHSTUFF_MAPPER_H
#define SCRATCHSTUFF_MAPPER_H

#include<string>
#include<vector>
#include<map>
#include <boost/algorithm/string.hpp>

class Mapper {
// Private data members
private:
    std::string inputFileName;
    std::string inputFileLine;
    std::string tempDirectory;

    //
public:
    // Default Constructor
    Mapper();

    // Initialization Constructor
    explicit Mapper(const std::string &input_file, const std::string &input_line, const std::string &temp_directory);

    // Setters
    // This will set the inputFileName private data member within the Mapper object
    void setInputFileName(const std::string &input_file);

    // This will set the inputFileLine private data member within the Mapper object
    void setInputFileLine(const std::string &input_line);

    // This will set the tempDirectory private data member within the Mapper object
    void setTempDirectory(const std::string &temp_directory);

    // Getters
    // This will retrieve the inputFileName private data member
    std::string getInputFileName();

    // This will retrieve the inputFileLine private data member
    std::string getInputFileLine();

    // This will retrieve the tempDirectory private data member
    std::string getTempDirectory();

    // This method will lowercase and remove punctuations - standardize a line
    std::string lowerRemovePunc(const std::string &wholeString);

    // This method will tokenize a line and return a vector of tokens - expects a standardized line
    std::vector<std::map<std::string, int>> tokenize(const std::string &cleanedUpString);

    // Primary Map method
    // It will read a line and tokenize the line into individual words
    // The method will create a map containing the originating file name and a vector of maps
    // Each map will contain a word and the occurrence of that word (1)
    std::map<std::string, std::vector<std::map<std::string, int>>> mapOperations();



};


#endif //SCRATCHSTUFF_MAPPER_H
