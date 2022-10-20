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
    // 3) sorter - it will read an object in memory which was result of Sorter operation and write to a temp directory
    // 4) output - it will read an object in memory which was result of Reducer operation and write to a final directory
    std::string directoryOperation;
    // Input Directory path used for input operation
    std::string inputDirectoryPath;
    // Result object from Mapper operation
    std::map<std::string, std::vector<std::vector<std::vector<std::tuple<std::string, int, int>>>>> mapperData;


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

    // Setter methods
    // This will set the FileProcessor's desired operation in private data member directoryOperation
    void setOperation(const std::string &operation);

    // This will set the FileProcessor's directory path that contain files in private data member inputDirectoryPath
    void setInputDirectoryPath(const std::string &directory_path);

    // This will set the FileProcessor's mapper Data private data member
    void setMapperData(const std::map<std::string, std::vector<std::vector<std::vector<std::tuple<std::string, int, int>>>>> &map_result);

    // Getter methods
    // This will retrieve the private data member directoryOperation
    std::string getOperation();

    // This will retrieve the private data member inputDirectoryPath
    std::string getInputDirectoryPath();

    // This will retrieve the mapper data private data member
    std::map<std::string, std::vector<std::vector<std::vector<std::tuple<std::string, int, int>>>>> getMapperData();

    // File lines
    int linesPerFile(const std::string &fileName);

    // Input operations - write out a map containing vector of vectors
    std::map<std::string, std::vector<std::vector<std::string>>> readDirectory();

    // This method will write corresponding data points to disk
    // It will return the directory name where data is being written to.
    std::string writeDirectory();

    // Entry method TODO
    void entryMethod();



};


#endif //SCRATCHSTUFF_FILEPROCESSOR_H
