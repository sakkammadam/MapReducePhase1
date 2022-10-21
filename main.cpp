#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <tuple>
#include <vector>
#include "FileProcessor.h"
#include "Mapper.h"
#include <boost/log/trivial.hpp>


int main(int argc, char* argv[]) {
    // Declare the file being processed
    //char* filePathBase = argv[1];
    //std::string filePath(filePathBase);

    // Create a testing object called testingFoo -- the directory path should be filePath - line #13
    FileProcessor testingFoo(
            "input",
            "/Users/AJEsparza/syr/CSE_687/shakespeare"
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
    std::string tempDirectory = testingMap2Disk.writeDirectory();

    // Please log this - @Hal, @Abraham - TODO
    std::cout << "Output of Mapper operations have been written to " << tempDirectory << std::endl;

    // message output for logging error, warnings, info, fatal, etc
    // Need to get it output on a file
    BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
    BOOST_LOG_TRIVIAL(info) << "An informational severity message";
    BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
    BOOST_LOG_TRIVIAL(error) << "An error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";


    return 0;
}
