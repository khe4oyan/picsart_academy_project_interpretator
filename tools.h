#pragma once
void first_w_space_del();
void GNL();
void error(std::string msg = "undefined behaviour");
void warning(std::string msg);

void first_white_space_del() {
	while (CODE_LINE[0] == '\t' || CODE_LINE[0] == ' ') {
		CODE_LINE.erase(0, 1);
	}
}

void GNL() {// Get Next Line
	std::getline(CODE, CODE_LINE);
	first_white_space_del();
	line_pointer++;
}

void error(std::string msg) {
	std::cout << "ERROR in " << line_pointer << " line: " << msg << std::endl;
	exit(0);
}

void warning(std::string msg) {
	std::cout << "WARNING in " << line_pointer << " line: " << msg << std::endl;
}