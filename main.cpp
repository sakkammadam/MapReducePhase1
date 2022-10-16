#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "FileProcessor.h"

int main(int argc, char* argv[]) {
    // Declare the file being processed
    //char* filePathBase = argv[1];
    //std::string filePath(filePathBase);
    /*
    // Please ignore !
    std::string filePath = "/home/sakkammadam/Documents/syr/cse687/projects/input_files/shakespeare/AsYouLIkeIte.txt";
    std::cout << "Processing file: " << filePath << std::endl;
    std::cout << "File directory: " << filePath.substr(0,filePath.rfind('/')+1) << std::endl;
    std::cout << "File name: " << filePath.substr(filePath.rfind('/')+1) << std::endl;

    std::string fileDirectory = filePath.substr(0,filePath.rfind('/')+1);
    std::string fileName = filePath.substr(filePath.rfind('/')+1);
    */

    //FileProcessor
    /*
    auto testing = new FileProcessor("input",
                                     "/home/sakkammadam/Documents/syr/cse687/projects/input_files/sample/AsYouLIkeIte.txt"
    );
    */


    FileProcessor testingFoo("input",
                             "/home/sakkammadam/Documents/syr/cse687/projects/input_files/shakespeare/"
    );

    std::cout << testingFoo.getDirectoryPath() << std::endl;

    std::cout << testingFoo.getOperation() << std::endl;

    std::map<std::string, std::vector<std::vector<std::string>>> directoryData = testingFoo.readDirectory();


    // Read the map variable!
    /*
    std::cout << "The map variable (directoryData)is displayed below ..." << std::endl;
    for(auto itr = directoryData.begin(); itr != directoryData.end(); ++itr){
        std::cout << '\t' << "Reading the file: " << itr->first << std::endl;
        std::cout << '\t' << "It has " << (itr->second).size() << " partitions" << std::endl;
        for(auto i=0; i < itr->second.size(); i++){
            std::cout << "Partition#" << i << std::endl;
            for(auto j=0; j < itr->second[i].size(); j++){
                std::cout << "\t\t" << itr->second[i][j] << std::endl;
            }
        }
    }

    */



    /*
     * Commenting for timebeing -
    // Lets declare a map
    std::map<std::string, std::vector<std::vector<std::string>>> foo;

    // Number of partitions
    int numPartitions = 8;

    // Declare a vector of vectors that contain strings
    std::vector<std::vector<std::string>> ioFiles;

    // Read the file as an input stream
    std::ifstream input(filePath);

    // Initialize the total lines per file
    int numLines = 0;

    // declare a line variable
    std::string line;

    // Read the input file and find the total number of lines
    while(std::getline(input, line)){
        ++numLines;
    }

    // Simple analysis
    std::cout << "The file " << filePath << " has " << numLines << " lines." << std::endl;


    // Reset the input file to beginning - we are clearing the input buffer here
    input.clear();
    // Reset it to beginning of the file
    input.seekg(0, std::ios::beg);

    // Determine number of lines per partition
    int numLinesPerPartition = numLines/numPartitions;

    // Represent the current line number
    int currentLine = 0;

    // Initialize partition
    int partition = 0;

    // Preemptively declare a vector of strings
    std::vector<std::string> simple;

    // Parse the file -
    while(std::getline(input, line)){
        // push each line into the vector of strings
        simple.push_back(line);
        // increment the currentLine variable
        ++currentLine;
        // if the lines falls outside the partition, then we need to push it to a new partition!
        if(currentLine >= (partition + 1) * numLinesPerPartition && partition < numPartitions -1){
            // increase the partition count
            ++partition;
            // push it to ioFiles (the vector of string vectors)
            ioFiles.push_back(simple);
            // recreate the simple vector
            std::vector<std::string> simple;
        }
    }

    // Insert into map - this contains all data for that one file!
    foo.insert({filePath, ioFiles});

    // Read the map variable!
    std::cout << "The map variable is displayed below ..." << std::endl;
    for(auto itr = foo.begin(); itr != foo.end(); ++itr){
        std::cout << '\t' << itr->first << std::endl;
        std::cout << '\t' << (itr->second).size() << std::endl;
        for(auto i=0; i < itr->second.size(); i++){
            std::cout << "Partition#" << i << std::endl;
            for(auto j=0; j < itr->second[i].size(); j++){
                std::cout << "\t\t" << itr->second[i][j] << std::endl;
            }
        }
    }

    */

    return 0;
}
