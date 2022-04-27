#pragma once
void warning(std::string msg);
void error(std::string msg = "undefined behaviour");

void error(std::string msg) {
	std::cout << "ERROR: " << msg << " line: " << line << std::endl;
	exit(0);
}

void warning(std::string msg) {
	std::cout << "WARNING: " << msg << " in line: " << line << std::endl;
}
