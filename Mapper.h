//
// Created by sakkammadam on 10/16/22.
//

#ifndef SCRATCHSTUFF_MAPPER_H
#define SCRATCHSTUFF_MAPPER_H

#include <string>
#include <tuple>
#include <vector>
#include <map>
#include <boost/algorithm/string.hpp>

class Mapper {
// Private data members
private:
    std::string inputFileName;
    std::string inputFileLine;
    std::string tempDirectory;
    int linePartitionNumber;

    //
public:
    // Default Constructor
    Mapper();

    // Initialization Constructor
    explicit Mapper(
            // The originating input file name with fully qualified path
            const std::string &input_file,
            // A line within the file which we are trying to standardize and tokenize
            const std::string &input_line,
            // temporary directory where we would like to store mapped data
            const std::string &temp_directory,
            // originating partition number the line belongs to
            int partition_line_number
            );

    // Setters
    // This will set the inputFileName private data member within the Mapper object
    void setInputFileName(const std::string &input_file);

    // This will set the inputFileLine private data member within the Mapper object
    void setInputFileLine(const std::string &input_line);

    // This will set the tempDirectory private data member within the Mapper object
    void setTempDirectory(const std::string &temp_directory);

    // This will set the linePartitionNumber private data member within the Mapper object
    void setLinePartitionNumber(int partition_line_number);

    // Getters
    // This will retrieve the inputFileName private data member
    std::string getInputFileName();

    // This will retrieve the inputFileLine private data member
    std::string getInputFileLine();

    // This will retrieve the tempDirectory private data member
    std::string getTempDirectory();

    // This will retrieve the linePartitionNumber private data member
    int getLinePartitionNumber();


    // This method will lowercase and remove punctuations - standardize a line
    std::string lowerRemovePunc(const std::string &wholeString);

    // This method will tokenize a line and return a vector of tokens within tuples- expects a standardized line
    // Each tuple will contain token, integer(1), partition# the originating line belonged to
    std::vector<std::tuple<std::string, int, int>> tokenize(const std::string &cleanedUpString, int linePartitionNum);

    // Primary Map method
    // It will read a line and tokenize the line into individual words
    // The method will create a map containing the originating file name and a vector of maps
    // Each map will contain a word and the occurrence of that word (1)
    std::map<std::string, std::vector<std::tuple<std::string, int, int>>> mapOperations();



};


#endif //SCRATCHSTUFF_MAPPER_H
