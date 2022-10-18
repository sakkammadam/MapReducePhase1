//
// Created by sakkammadam on 10/16/22.
//

#include "Mapper.h"
#include <string>
#include <filesystem>
#include <vector>
#include <map>
#include <tuple>
#include <boost/algorithm/string.hpp>

// Default constructor
Mapper::Mapper():inputFileName{" "},inputFileLine{" "},tempDirectory{" "},linePartitionNumber{} {
    // Nothing in the body of the default constructor
    // Note that we have set the private data members as blank!
}

Mapper::Mapper(
        // The originating input file name with fully qualified path
        const std::string &input_file,
        // A line within the file which we are trying to standardize and tokenize
        const std::string &input_line,
        // temporary directory where we would like to store mapped data
        const std::string &temp_directory,
        // originating partition number the line belongs to
        int partition_line_number
        ) {
    // Call input file name setter
    setInputFileName(input_file);
    // Call input line setter
    setInputFileLine(input_line);
    // Call temporary directory setter
    setTempDirectory(temp_directory);
    // Call line partition number setter
    setLinePartitionNumber(partition_line_number);
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

// This will set the linePartitionNumber private data member within the Mapper object
void Mapper::setLinePartitionNumber(int partitionLine) {
    this->linePartitionNumber = partitionLine;

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

// This will retrieve the linePartitionNumber private data member
int Mapper::getLinePartitionNumber() {
    return this->linePartitionNumber;
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
std::vector<std::tuple<std::string, int, int>> Mapper::tokenize(const std::string &cleanedUpString, int linePartitionNum) {
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
std::map<std::string, std::vector<std::tuple<std::string, int, int>>> Mapper::mapOperations() {
    // let's cleanup the original string by creating a copy - see lowerRemovePunc method
    std::string cleanedString = lowerRemovePunc(getInputFileLine());
    // let's create a vector containing maps of tokens from the cleaned up string
    std::vector<std::tuple<std::string, int, int>> stringTokens = tokenize(cleanedString, getLinePartitionNumber());
    // A map that maps the original file name and associated line, which has been converted to vector of token maps
    std::map<std::string, std::vector<std::tuple<std::string, int, int>>> fileLineTokenMapper;
    // Let's insert into the above map
    fileLineTokenMapper.insert({getInputFileName(), stringTokens});
    // return it so that it can be used later
    return fileLineTokenMapper;
}


