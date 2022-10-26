//
// Created by sakkammadam on 10/16/22.
//

#include "Mapper.h"
#include <iostream>
#include <string>
#include <filesystem>
#include <sstream>
#include <vector>
#include <map>
#include <tuple>

// Default constructor
Mapper::Mapper(){
    // Nothing in the body of the default constructor
    // Note that we have set the private data members as blank!
}

Mapper::Mapper(
        // Get the processed directory object
        const std::map<std::string, std::vector<std::vector<std::string>>> &processed_directory
        ) {
    // This will set the processedDirectory private data member within the Mapper object
    setProcessedDirectory(processed_directory);
    // Entry method - to be added
}

// Setters
// This will set the processedDirectory private data member within the Mapper object
void Mapper::setProcessedDirectory(const std::map<std::string, std::vector<std::vector<std::string>>> &processed_directory) {
    this->processedDirectory = processed_directory;
}

// Getters
// This will retrieve the processedDirectory private data member within the Mapper object
std::map<std::string, std::vector<std::vector<std::string>>> Mapper::getProcessedDirectory() {
    return this->processedDirectory;
}

// Cleanup methods -
// 1) lowerRemovePunc - This method will lowercase and remove punctuations, essentially standardize a line
// 2) tokenize - This method will tokenize a line and return a vector of tokens - expects a cleaned up line

// This method will lowercase and remove punctuations - standardize a line
std::string Mapper::lowerRemovePunc(const std::string &wholeString) {
    // declare a temporary string
    std::string temp;
    // let's iterate over the "wholeString" string container, a character at a time -
    for(auto character: wholeString){
        // if it's a newline - do nothing
        if(character == '\n'){
            // do nothing
        } else if(!std::ispunct(character)){
            // if it's not a punctuation character - add it to temp string
            temp += tolower(character, std::locale());
        } else {
            // adding for syntax - nothing should come here
        }
    }
    // return the temporary string
    return temp;
}

// This method will tokenize a line and return a vector containing tuples of tokens
// expects a cleaned up line
std::vector<std::tuple<std::string, int, int>> Mapper::tokenize(const std::string &cleanedUpString, size_t linePartitionNum) {
    // default 1 integer
    int defOne = 1;
    // declare a vector containing maps of tokens
    std::vector<std::tuple<std::string, int, int>>  tokens;
    // leverage stringstream to read string as a stream which will be piped into another string using getline
    std::stringstream baseLine(cleanedUpString);
    // declare a token representing each word within a stream
    std::string token;
    // Using getline to split the baseLine string using whitespace as a delimiter
    while(getline(baseLine, token, ' ')){
        // empty check is to handle the edge case where there were multiple spaces
        if(!token.empty()){
            // declare a map
            std::tuple<std::string, int, int> tempTuple;
            // insert into tempTuple the token, 1, and originating line's partition number
            tempTuple = std::make_tuple(token, defOne, linePartitionNum);
            // push into the tokens vector
            tokens.push_back(tempTuple);
        }
    }
    // return tokens vector
    return tokens;
}

// Primary Mapper Operations!
// This method will internally call - 1) lowerRemovePunc and 2) tokenize method
// This method will take a line in the file, standardize it by removing punctuations, lowercase and creates tokens
std::vector<std::tuple<std::string, int, int>> Mapper::mapLine(const std::string &fileLine, size_t partitionNum) {
    // let's cleanup the original string by creating a copy - see lowerRemovePunc method
    std::string cleanedString = lowerRemovePunc(fileLine);
    // let's create a vector containing maps of tokens from the cleaned up string
    std::vector<std::tuple<std::string, int, int>> stringTokens = tokenize(cleanedString, partitionNum);
    // return it so that it can be used later
    return stringTokens;
}

// Overarching MapOperations method that acts against all lines of a file
std::map<std::string, std::vector<std::vector<std::vector<std::tuple<std::string, int, int>>>>> Mapper::mapOperations() {
    // let's declare an output map
    std::map<std::string, std::vector<std::vector<std::vector<std::tuple<std::string, int, int>>>>> outputMapperData;
    // let's invoke the private data member
    for(const auto &fileData: getProcessedDirectory()){
        std::cout << "Mapping data from: " << fileData.first << std::endl;
        // now we are going to read ALL the data associated for a particular file
        std::cout << "The data has " << fileData.second.size() << " partitions." << std::endl;
        // Declare a file vector - it contains partition vectors
        std::vector<std::vector<std::vector<std::tuple<std::string, int, int>>>> fileVector;
        // Reading each partition...
        for(size_t partition=0; partition < fileData.second.size(); ++partition){
            // Declare a partition vector
            std::vector<std::vector<std::tuple<std::string, int, int>>> partitionVector;
            std::cout << "Partition#" << partition << " has " << fileData.second[partition].size() << " records" << std::endl;
            // Now for each partition, we are going to read each line!
            for(size_t line=0; line < fileData.second[partition].size(); ++line){
                // here we will call the mapLine method to clean and tokenize each line
                std::vector<std::tuple<std::string, int, int>> line2Tokens = mapLine(fileData.second[partition][line],line);
                // push it to the partition vector
                partitionVector.push_back(line2Tokens);
            }
            // Push each partition vector back to file vector
            fileVector.push_back(partitionVector);
        }
        // Insert the file name and associated vector spaces into Output mapper
        outputMapperData.insert({fileData.first, fileVector});
    }
    // return outputMapperData for downstream processing
    return outputMapperData;
}