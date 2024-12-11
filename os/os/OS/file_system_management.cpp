#include "file_system_management.h"
#include <string>
#include <iostream>
#include <fstream>

// 列出目录内容
void listDirectory(const std::string& path) {
	try {
		for (const auto& entry : fs::directory_iterator(path)) {
			std::cout << entry.path() << std::endl;
		}
	}
	catch (const fs::filesystem_error& e) {
		std::cerr << "\t" << e.what() << std::endl;
	}
}

// 读取文件内容
void readFile(const std::string& path) {
	std::ifstream file(path);
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			std::cout << line << std::endl;
		}
		file.close();
	}
	else {
		std::cerr << "Failed to open file for reading: " << path << std::endl;
	}
}