#include <iostream>
#include <map>
#include <fstream>
#include <string>

std::map<std::string, std::string> STRING_TYPE;
std::map<std::string, int> NUMB_TYPE;
std::map<std::string, bool> BOOL_TYPE;

std::fstream CODE ("variables.cpk");

void error(std::string msg = "undefined behaviour", int line = -1) {
	std::cout << "ERROR: " << msg;
	if (line > 0) {std::cout << " line: " << line << std::endl;}
	else {std::cout << std::endl;}
	
	exit(0);
}

void warning(std::string msg, int line = -1) {
	std::cout << "WARNING: " << msg;
	if (line > 0) { std::cout << " line: " << line << std::endl; }
	else { std::cout << std::endl; }
}

void variable_create(std::string text) {
	//std::cout << text << "\n";
	std::string tockens[3];

	int index = 0;
	std::string toc = "";
	int toc_count = 0;
	for (int i = 0; i < text.length(); ++i) {
		if (text[i] == '(' || text[i] == ',' || text[i] == ' ' || text[i] == ')') {
			if (toc_count >= 3) {error("You can entered only 2 arguments");}
			if (toc.length() != 0) {
				tockens[index++] = toc;
				toc = "";
				toc_count++;
			}
			continue;
		}
		toc += text[i];
	}

	

	for (int i = 0; i < 3; ++i) {
		std::cout << tockens[i] << " ";
	}
	std::cout << "\n";

	// tockens conditional
	if (tockens[0] == "num") { // NUMBER type
		try{
			if (!NUMB_TYPE.count(tockens[1])) {
				NUMB_TYPE[tockens[1]] = std::stoi(tockens[2]);
			}
			else {
				error("Variable name can was only one");
			}
		}
		catch (const std::exception&){
			error("Variable value is not a number");
		}
		
	}else

	if (tockens[0] == "str") { // STRING type
		if (!STRING_TYPE.count(tockens[1])) {
			if (tockens[2].length() == 0) {warning("argument is not indentified");}
			STRING_TYPE[tockens[1]] = tockens[2];
		}
		else {
			error("Variable name can was only one");
		}
	}else

	if (tockens[0] == "bool") { // BOOL type
		if (!BOOL_TYPE.count(tockens[1])) {
			if (tockens[2] == "false") {
				BOOL_TYPE[tockens[1]] = false;
			}
			else if (tockens[2] == "true") {
				BOOL_TYPE[tockens[1]] = true;
			}
			else {
				error("Only True or False");
			}
		}
		else {
			error("Variable name can was only one");
		}
	}
}

int main(){
	int line = 1;

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
	}
}