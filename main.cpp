#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

int main(int argc, char* argv[]) {
    // Declare the file being processed
    //char* filePathBase = argv[1];
    //std::string filePath(filePathBase);
    std::string filePath = "/home/sakkammadam/Documents/syr/cse687/projects/input_files/shakespeare/AsYouLIkeIte.txt";
    std::cout << "Processing file: " << filePath << std::endl;
    std::cout << "File directory: " << filePath.substr(0,filePath.rfind('/')+1) << std::endl;
    std::cout << "File name: " << filePath.substr(filePath.rfind('/')+1) << std::endl;

    std::string fileDirectory = filePath.substr(0,filePath.rfind('/')+1);
    std::string fileName = filePath.substr(filePath.rfind('/')+1);

    // Lets declare a map
    std::map<std::string, std::vector<std::vector<std::string>>> foo;

    // Number of partitions
    int numPartitions = 8;

    // lets initialize output files
    //std::vector<std::string> ioFiles(numPartitions);

    std::vector<std::vector<std::string>> ioFiles;

    /*
    for(int partition = 0; partition < numOfPartitions; ++partition){
        outputFiles[partition].open(fileDirectory + '/' + fileName + '.' + std::to_string(partition));
     }
    */
    /* Read the file as an input stream */
    std::ifstream input(filePath);

    /* Count the number of lines */
    int numLines = 0;
    std::string line;
    while(std::getline(input, line)){
        ++numLines;
    }
    std::cout << "The file " << filePath << " has " << numLines << " lines." << std::endl;
    /* Reset the input file to beginning */
    input.clear();
    input.seekg(0, std::ios::beg);

    // Determine number of lines per partition
    int numLinesPerPartition = numLines/numPartitions;

    // Represent the current line number
    int currentLine = 0;

    // Initialize partition
    int partition = 0;

    std::vector<std::string> simple;

    // Parse the file -
    while(std::getline(input, line)){
        simple.push_back(line);
        ++currentLine;
        if(currentLine >= (partition + 1) * numLinesPerPartition && partition < numPartitions -1){
            // increase the partition count
            ++partition;
            // push it to ioFiles
            ioFiles.push_back(simple);
            // recreate the simple vector
            std::vector<std::string> simple;
        }
    }

    // Insert into map
    foo.insert({filePath, ioFiles});

    // Declare an iterator
    //std::map<std::string, std::vector<std::vector<std::string>>>::iterator itr;

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

    return 0;
}
