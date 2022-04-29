#include <iostream>
#include <fstream>
#include <string>

enum mods{DEFAULT, CYCLE, CONDITION, SKIP};

std::string VARIABLES;
std::fstream CODE ("variables.cpk");
int line_pointer = 1; // for easy errors show line
mods READ_MODE = DEFAULT;
std::string CODE_LINE;

#include "tools.h"

std::string get_first_key() {
	std::string fk;

	for (int i = 0; i < CODE_LINE.length(); ++i) {
		if (CODE_LINE[i] == ' ' || CODE_LINE[i] == '}') {
			break;
		}
		fk += CODE_LINE[i];
	}

	return fk;
}

void find_variable(std::string varName) {
	
}

void try_variable_create() {
	// check have this variable or not
	std::string tockens[3];
	int index = 0;

	for (int i = 0; i < CODE_LINE.length(); ++i) {
		if (CODE_LINE[i] == ';') {break;}
		if (CODE_LINE[i] == ' ') {index++;}
		tockens[index] += CODE_LINE[i];
	}

	// find variable name tockens[1] in VARIABLES
	find_variable(tockens[1]);
}

void default_mode() {
	if (CODE_LINE.length() == 0) { return; }
	//std::cout << "Get line: " << CODE_LINE << "\n";

	std::string first_keyword = get_first_key();

	std::cout << "- Keyword: " << first_keyword << std::endl;
	if (first_keyword == "num" || first_keyword == "str" || first_keyword == "bool") {
		try_variable_create();
	}else
	if (first_keyword == "if") {
		// if logic function
	}else
	if(first_keyword == "for") {
		// for logic function
	}
	if (first_keyword == "else") {
		READ_MODE = SKIP;
	}
}

void cycle_mode() {

}

void condition_mode() {

}

void skip_mode() {
	while (CODE_LINE != "}") {
		GNL();
	}
	
	READ_MODE = DEFAULT;
}

void line_read(){
	while (!CODE.eof()) {
		GNL();
		if (READ_MODE == DEFAULT) {
			default_mode();
		}
		else if (READ_MODE == CYCLE) {
			cycle_mode();
		}
		else if (READ_MODE == SKIP) {
			skip_mode();
		}
		else {
			condition_mode();
		}

		line_pointer++;
	}
}

int main(){
	line_read();
}