#include <fstream>
#include <iostream>
#include "Utilities.h"


char* readFile(const char* filePath){
	std::ifstream file(filePath, std::ios::in | std::ios::binary | std::ios::ate);
	if (file.is_open()){
		file.seekg(0, std::ios::end);
		int size = file.tellg();
		char* contents = new char[size];
		file.seekg(0, std::ios::beg);
		file.read(contents, size);
		file.close();
		return contents;
	}
	else{
		std::cout << "ERROR! Can't open file!\n";
	}
	return NULL;
}