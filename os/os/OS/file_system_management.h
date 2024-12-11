#ifndef FILE_SYSTEM_MANAGEMENT_H
#define FILE_SYSTEM_MANAGEMENT_H
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

#include <iostream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

// º¯ÊýÉùÃ÷
void listDirectory(const std::string& path);
void readFile(const std::string& path);

#endif