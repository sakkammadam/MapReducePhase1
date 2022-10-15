//
// Created by sakkammadam on 10/13/22.
//

#ifndef SCRATCHSTUFF_FILEPROCESSOR_H
#define SCRATCHSTUFF_FILEPROCESSOR_H

#include<string>
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
    FileProcessor(const std::string &operation, const std::string &directory_path);

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

    // Input operations
    std::map<std::string, std::vector<std::ofstream>> readDirectory();

    // Output operations
    void writeDirectory();

    // Entry method
    void entryMethod();



};


#endif //SCRATCHSTUFF_FILEPROCESSOR_H
