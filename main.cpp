#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <tuple>
#include <vector>
#include <filesystem>
#include "FileProcessor.h"
#include "Mapper.h"
#include "Shuffler.h"

int main(int argc, char* argv[]) {
    // Declare the file being processed
    //char* filePathBase = argv[1];
    //std::string filePath(filePathBase);


    // Create a testing object called testingFoo -- the directory path should be filePath - line #13
    FileProcessor testingFoo(
            "input",
            "/home/sakkammadam/Documents/syr/cse687/projects/input_files/shakespeare"
            );

    // Retrieve private data members - directory and requested operation (input)
    std::cout << testingFoo.getInputDirectoryPath() << std::endl;
    std::cout << testingFoo.getOperation() << std::endl;
    // Create a variable that will host all data that is present along the path
    std::map<std::string, std::vector<std::vector<std::string>>> directoryData = testingFoo.readDirectory();

    // declare a peek vector
    std::map<std::string, std::vector<std::vector<std::vector<std::tuple<std::string, int, int>>>>> peek;

    // Read the map variable! and confirm the data is represented correctly!
    Mapper mapTest(directoryData);
    peek = mapTest.mapOperations();

    // Create a File Processor object that will write output of Mapper class to disk
    FileProcessor testingMap2Disk("mapper",peek);
    std::string mapDirectory = testingMap2Disk.writeDirectory();

    // Please log this - @Hal, @Abraham - TODO
    std::cout << "Output of Mapper operations have been written to " << mapDirectory << std::endl;



    Shuffler testingShuffle(mapDirectory);
    std::vector<std::map<std::string, std::map<std::string,size_t>>> blah;
    blah = testingShuffle.shuffleOperations();

    // let's provide result of shuffle to FileProcessor to write them to disk
    FileProcessor testingShuffle2disk("shuffler",blah);
    std::string shuffleDirectory = testingShuffle2disk.writeDirectory();

    // Please log this - @Hal, @Abraham - TODO
    std::cout << "Output of shuffle operations have been written to " << shuffleDirectory << std::endl;


    return 0;
}
