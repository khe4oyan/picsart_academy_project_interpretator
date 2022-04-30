#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <Windows.h>

enum mods { DEFAULT, CYCLE, CONDITION, SKIP };

struct Var {
	std::string type;
	std::string value;
};

std::fstream CODE("variables.cpk"); // path for programm code file
std::string TOCKENS[4]; // every line devided in tockens
std::string CODE_LINE; // get new line 
std::map<std::string, Var> VARIABLES; // all variables with their value and type
int line_pointer = 0; // for easy errors show line
mods READ_MODE = DEFAULT; 

#include "tools.h"
void skip_mode();

void cnt_else_version() {
	skip_mode();
	GNL();
	if (TOCKENS[0] == "else") {
		READ_MODE = CONDITION;
	}
}

void cnt_type_equal(std::string type) {
	if (VARIABLES[TOCKENS[1]].type != type || VARIABLES[TOCKENS[3]].type != type) {
		error("you can use this operator only with num types");
	}
}

void cnt_big() { // >
	cnt_type_equal("num");

	// do..
	if (std::stoi(VARIABLES[TOCKENS[1]].value) > std::stoi(VARIABLES[TOCKENS[3]].value)) {
		READ_MODE = CONDITION;
	}
	else {
		cnt_else_version();
	}
}

void cnt_small() { // <
	cnt_type_equal("num");

	if (std::stoi(VARIABLES[TOCKENS[1]].value) < std::stoi(VARIABLES[TOCKENS[3]].value)) {
		READ_MODE = CONDITION;
	}
	else {
		cnt_else_version();
	}
}

void cnt_equal() { // == 
	if (VARIABLES[TOCKENS[1]].value == VARIABLES[TOCKENS[3]].value) {
		READ_MODE = CONDITION;
	}
	else {
		cnt_else_version();
	}
}
void cnt_not_equal() { // != 
	if (VARIABLES[TOCKENS[1]].value != VARIABLES[TOCKENS[3]].value) {
		READ_MODE = CONDITION;
	}
	else {
		cnt_else_version();
	}
}
void cnt_and() { // && 
}
void cnt_or() { // || 
}

void cnt_opeartors(std::string opr) {
	// >, <, ==, !=, &&, ||
	
	if(opr == ">") { cnt_big(); } else
	if(opr == "<") { cnt_small(); } else
	if(opr == "==") { cnt_equal(); } else
	if(opr == "!=") { cnt_not_equal(); } else
	if(opr == "&&") { cnt_and(); } else
	if(opr == "||") { cnt_or(); } else
	error("undefined condition operator");
}

void condition() {
	std::string left_var = TOCKENS[1];
	std::string right_var = TOCKENS[3];
	if (!var_found(left_var) || !var_found(right_var)) {
		error("this variable is exists");
	}

	if (VARIABLES[left_var].type != VARIABLES[right_var].type) {
		error("condition values types isn't equal");
	}

	cnt_opeartors(TOCKENS[2]);

/*
	GNL();
	if (TOCKENS[0] == "else") {
		READ_MODE = SKIP;
	}
*/
}

void create_var() {
	if (var_found(TOCKENS[1])) {
		error("this name is exists");
	}

	if (TOCKENS[0] == "num") {
		for (int i = 0; i < TOCKENS[2].length(); ++i) {
			if (TOCKENS[2][i] >= 48 && TOCKENS[2][i] <= 57) {
				continue;
			}
			error("you can't appropriate symbol for number type");
		}
	}

	VARIABLES[TOCKENS[1]] = { TOCKENS[0], TOCKENS[2] };
}

void default_mode() {
	if (CODE_LINE.length() == 0) { return; }
	//std::cout << "Get line: " << CODE_LINE << "\n";

	std::string first_keyword = TOCKENS[0];

	if (TOCKENS[1] != "=") {
		if (first_keyword == "num" || first_keyword == "str" || first_keyword == "bool") { create_var(); }else
		if (first_keyword == "if") { condition(); }else
		if (first_keyword == "for") { READ_MODE = SKIP; /* временно */ } else
		if (first_keyword == "else") { READ_MODE = SKIP; }else
		if (first_keyword == "output") { }
		else { error("syntax error"); }
	}
	else {
		// присвоение 
		error("in developing..");
	}
}
 
void cycle_mode() {

}

void condition_mode() {
	while (CODE_LINE != "}") {
		default_mode();
		GNL();
	}
	GNL();

	if (CODE_LINE == "else;") { READ_MODE = SKIP; }
	else { READ_MODE = DEFAULT; }
}

void skip_mode() {
	while (CODE_LINE != "}") {
		GNL();
	}

	READ_MODE = DEFAULT;
}

void line_read() {
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
	}
}

int main() {
	line_read();
}