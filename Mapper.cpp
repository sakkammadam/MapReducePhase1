//
// Created by sakkammadam on 10/16/22.
//

#include "Mapper.h"
#include<string>
#include<filesystem>
#include<vector>
#include<map>
#include <boost/algorithm/string.hpp>

// Default constructor
Mapper::Mapper():inputFileName{" "},inputFileLine{" "},tempDirectory{" "} {
    // Nothing in the body of the default constructor
    // Note that we have set the private data members as blank!
}

Mapper::Mapper(const std::string &input_file, const std::string &input_line, const std::string &temp_directory) {
    // Call input file name setter
    setInputFileName(input_file);
    // Call input line setter
    setInputFileLine(input_line);
    // Call temporary directory setter
    setTempDirectory(temp_directory);
    // Entry method - to be added
}

// sets the input file name private data member
void Mapper::setInputFileName(const std::string &input_file) {
    std::filesystem::path p(input_file);
    if(std::filesystem::exists(p)){
        this->inputFileName = input_file;
    } else {
        throw std::runtime_error("Input file not found!: " + input_file );
    }
}

// sets the input file line private data member
void Mapper::setInputFileLine(const std::string &input_line) {
    // assign
    this->inputFileLine = input_line;
}

// sets the temp directory private data member - if directory not present, will be created
void Mapper::setTempDirectory(const std::string &temp_directory) {
    std::filesystem::path p(temp_directory);
    if(std::filesystem::exists(p)){
        // assign
        this->tempDirectory = temp_directory;
    } else {
        // create directory!
        std::filesystem::create_directory(temp_directory);
        // then assign
        this->tempDirectory = temp_directory;
    }
}

// Getters
// This will retrieve the inputFileName private data member
std::string Mapper::getInputFileName() {
    return this->inputFileName;
}

// This will retrieve the inputFileLine private data member
std::string Mapper::getInputFileLine() {
    return this->inputFileLine;
}

// This will retrieve the tempDirectory private data member
std::string Mapper::getTempDirectory() {
    return this->tempDirectory;
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

// This method will tokenize a line and return a vector containing maps of tokens
// expects a cleaned up line
std::vector<std::map<std::string, int>> Mapper::tokenize(const std::string &cleanedUpString) {
    // declare a vector containing maps of tokens
    std::vector<std::map<std::string, int>>  tokens;
    // leverage stringstream to read string as a stream which will be piped into another string using getline
    std::stringstream baseLine(cleanedUpString);
    // declare a token representing each word within a stream
    std::string token;
    // Using getline to split the baseLine string using whitespace as a delimiter
    while(getline(baseLine, token, ' ')){
        // empty check is to handle the edge case where there were multiple spaces
        if(!token.empty()){
            // declare a map
            std::map<std::string, int> tempMap;
            // insert into tempMap the token
            tempMap.insert({token, 1});
            // push into the tokens vector
            tokens.push_back(tempMap);
        }
    }
    // return tokens vector
    return tokens;
}

// Primary Mapper Operations!
// This method will internally call - 1) lowerRemovePunc and 2) tokenize method
std::map<std::string, std::vector<std::map<std::string, int>>> Mapper::mapOperations() {
    // let's cleanup the original string by creating a copy - see lowerRemovePunc method
    std::string cleanedUpString = lowerRemovePunc(this->inputFileLine);
    // let's create a vector containing maps of tokens from the cleaned up string
    std::vector<std::map<std::string, int>> stringTokens = tokenize(cleanedUpString);
    // A map that maps the original file name and associated line, which has been converted to vector of token maps
    std::map<std::string, std::vector<std::map<std::string, int>>> fileLineTokenMapper;
    // Let's insert into the above map
    fileLineTokenMapper.insert({this->inputFileName, stringTokens});
    // return it so that it can be used later
    return fileLineTokenMapper;
}



