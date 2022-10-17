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


    // Create a testing object called testingFoo
    FileProcessor testingFoo(
            "input",
            "/home/sakkammadam/Documents/syr/cse687/projects/input_files/shakespeare/"
            );

    // Retrieve private data members - directory and requested operation (input)
    std::cout << testingFoo.getDirectoryPath() << std::endl;
    std::cout << testingFoo.getOperation() << std::endl;
    // Create a variable that will host all data that is present along the path
    std::map<std::string, std::vector<std::vector<std::string>>> directoryData = testingFoo.readDirectory();

    // Read the map variable! and confirm the data is represented correctly!
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

    return 0;
}
