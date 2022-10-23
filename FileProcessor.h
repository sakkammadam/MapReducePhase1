//
// Created by sakkammadam on 10/13/22.
//

#ifndef SCRATCHSTUFF_FILEPROCESSOR_H
#define SCRATCHSTUFF_FILEPROCESSOR_H
/////////////////////////////////////////////////////////////////////////////////////////////////////
///    FileProcessor.h - handles file processing actions                                          ///
///    v0.1                                                                                       ///
///    Language: C++, Clion 2022.2.4                                                              ///
///    Platform: Ubuntu 20.04 LTS                                                                 ///
///    Author: Sooraj Akkammadam                                                                  ///
/////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Package Introduction:
 * ---------------------------------------------------------------
 * This package provides the interface for the FileProcessor class
 * ---------------------------------------------------------------
 * Package Operations:
 *  Explain each method
 *
 * Build Process:
 * ----------------
 *  Required Files: FileProcessor.h, FileProcessor.cpp
 *
 */

#include <iostream>
#include <cmath>
#include <string>
#include <filesystem>
#include <fstream>
#include <map>
#include <vector>
#include <tuple>

class FileProcessor {
    // Private data members!
private:
    // Request type of operation -
    // 1) input - it will read all files along a directory path, which must be supplied
    // 2) mapper - it will read an object in memory which was result of Mapper operation and write to a temp directory
    // 3) shuffler - it will read an object in memory which was result of Sorter operation and write to a temp directory
    // 4) reducer - it will read an object in memory which was result of Reducer operation and write to a final directory
    std::string directoryOperation;
    // Input Directory path used for input operation
    std::string inputDirectoryPath;
    // Result object from Mapper operation
    std::map<std::string, std::vector<std::vector<std::vector<std::tuple<std::string, int, int>>>>> mapperData;
    // Result object from Shuffler operation
    std::vector<std::map<std::string, std::map<std::string, size_t>>> shufflerData;
    // Result object from Reducer operation
    std::vector<std::map<std::string, std::map<std::string, size_t>>> reducerData;


    // Public class functions!
public:
    // Default constructor
    FileProcessor();

    // Initialization constructor - used primarily for input operations
    explicit FileProcessor(const std::string &operation, const std::string &directory_path);

    // Initialization constructor - used primarily for mapper operations
    explicit FileProcessor(
            const std::string &operation,
            const std::map<std::string, std::vector<std::vector<std::vector<std::tuple<std::string, int, int>>>>> &map_result
            );

    // Initialization constructor - used primarily for shuffler and reducer operations
    explicit FileProcessor(
            const std::string &operation,
            const std::vector<std::map<std::string, std::map<std::string, size_t>>> &shuffle_or_reducer_result
    );


    // Setter methods
    // This will set the FileProcessor's desired operation in private data member directoryOperation
    void setOperation(const std::string &operation);

    // This will set the FileProcessor's directory path that contain files in private data member inputDirectoryPath
    void setInputDirectoryPath(const std::string &directory_path);

    // This will set the FileProcessor's mapper Data private data member
    void setMapperData(const std::map<std::string, std::vector<std::vector<std::vector<std::tuple<std::string, int, int>>>>> &map_result);

    // This will set the FileProcessor's shuffler data private data member
    void setShufflerData(const std::vector<std::map<std::string, std::map<std::string, size_t>>> &shuffle_result);

    // This will set the FileProcessor's reducer data private data member
    void setReducerData(const std::vector<std::map<std::string, std::map<std::string, size_t>>> &reducer_result);

    // Getter methods
    // This will retrieve the private data member directoryOperation
    std::string getOperation();

    // This will retrieve the private data member inputDirectoryPath
    std::string getInputDirectoryPath();

    // This will retrieve the mapper data private data member
    std::map<std::string, std::vector<std::vector<std::vector<std::tuple<std::string, int, int>>>>> getMapperData();

    // This will retrieve the shuffler data private data member
    std::vector<std::map<std::string, std::map<std::string, size_t>>> getShufflerData();

    // This will retrieve the reducer data private data member
    std::vector<std::map<std::string, std::map<std::string, size_t>>> getReducerData();

    // File lines - helper method within readDirectory
    int linesPerFile(const std::string &fileName);

    // Input operations
    // Create a map containing vector of vectors of data against input directory
    std::map<std::string, std::vector<std::vector<std::string>>> readDirectory();

    // Output operations

    // This method will create necessary directory paths
    void createDirectory(const std::string &directoryPath);

    // This method will write the outputs of Mapper Operations - it will return the directory of temp_mapper
    std::string writeMapperOutputs();

    // This method will write the outputs of Shuffle Operations - it will return the directory of temp_shuffler
    std::string writeShuffleOutputs();

    // This method will write the outputs of Reducer Operations - it will return the directory of final_output
    std::string writeReduceOutputs();

    // This method will write corresponding data points to disk
    // It will return the directory name where data is being written to.
    std::string writeDirectory();

};


#endif //SCRATCHSTUFF_FILEPROCESSOR_H
