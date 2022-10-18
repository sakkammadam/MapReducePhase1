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

#include <string>
#include <map>
#include <vector>

class FileProcessor {
    // Private data members!
private:
    std::string directoryOperation;
    std::string directoryPath;

    // Public class functions!
public:
    // Default constructor
    FileProcessor();

    // Initialization constructor
    explicit FileProcessor(const std::string &operation, const std::string &directory_path);

    // Setter methods
    // This will set the FileProcessor's desired operation in private data member directoryOperation
    void setOperation(const std::string &operation);

    // This will set the FileProcessor's directory path that contain files in private data member directoryPath
    void setDirectoryPath(const std::string &directory_path);

    // Getter methods
    // This will retrieve the private data member directoryOperation
    std::string getOperation();

    // This will retrieve the private data member directoryPath
    std::string getDirectoryPath();

    // File lines
    int linesPerFile(const std::string &fileName);

    // Input operations - write out a map containing vector of vectors
    std::map<std::string, std::vector<std::vector<std::string>>> readDirectory();

    // Output operations TODO
    void writeDirectory();

    // Entry method TODO
    void entryMethod();



};


#endif //SCRATCHSTUFF_FILEPROCESSOR_H
