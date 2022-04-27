#include <iostream>
#include <map>
#include <fstream>
#include <string>

std::map<std::string, std::string> STRING_TYPE;
std::map<std::string, int> NUMB_TYPE;
std::map<std::string, bool> BOOL_TYPE;
std::fstream CODE ("variables.cpk");
int line = 1; // for easy errors show line

#include "tools.h"
#include "variable.h"


int main(){

	while (!CODE.eof()){
		std::string code_line;
		std::getline(CODE, code_line);

		char line_type = code_line[0];
		switch (line_type) {
			case 'd': {
				variable_create(code_line.erase(0,2));
				break;
			}
			case 'e': {
				// conditional statements if else
				break;
			}
			case 'l': {
				// cicles
				break;
			}
			case 'o': {
				// output
				break;
			}
			default: {
				error();
				// see other version (variable use, etc..)
			}
		}

		line++;
	}
}