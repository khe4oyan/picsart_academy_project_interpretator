#pragma once

void condition_mode() {
	while (CODE_LINE != "}") {
		default_mode();
		GNL();
	}
	//GNL();

	if (CODE_LINE == "else;") { READ_MODE = SKIP; }
	else { READ_MODE = DEFAULT; }
}

void cnt_opeartors(std::string opr) {
	// >, <, ==, !=, &&, ||
	
	if (opr == ">") { cnt_big(); }else
	if (opr == "<") { cnt_small(); }else
	if (opr == "==") { cnt_equal(); }else
	if (opr == "!=") { cnt_not_equal(); }else
	if (opr == "&&") { cnt_and(); }else
	if (opr == "||") { cnt_or(); }else
	error("\"" + opr + "\"undefined condition operator");
}

void condition() {
	std::string left_var = TOCKENS[1];
	std::string right_var = TOCKENS[3];

	if (!var_found(right_var)) {
		error("\"" + left_var + "\" variable is exists");
	}

	if (!var_found(right_var)) {
		error("\"" + right_var + "\" variable is exists");
	}

	if (VARIABLES[left_var].type != VARIABLES[right_var].type) {
		error("condition values types isn't equal");
	}

	cnt_opeartors(TOCKENS[2]);
}

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

	int num_1 = std::stoi(VARIABLES[TOCKENS[1]].value);
	int num_2 = std::stoi(VARIABLES[TOCKENS[3]].value);

	if (num_1 > num_2) {READ_MODE = CONDITION;}
	else {cnt_else_version();}
}

void cnt_small() { // <
	cnt_type_equal("num");

	int num_1 = std::stoi(VARIABLES[TOCKENS[1]].value);
	int num_2 = std::stoi(VARIABLES[TOCKENS[3]].value);

	if (num_1 < num_2) { READ_MODE = CONDITION; }
	else {cnt_else_version();}
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
	cnt_type_equal("num");

	if (std::stoi(VARIABLES[TOCKENS[1]].value) > std::stoi(VARIABLES[TOCKENS[3]].value)) {
		READ_MODE = CONDITION;
	}
	else {cnt_else_version();}
}

void cnt_or() { // || 
	cnt_type_equal("num");

	if (std::stoi(VARIABLES[TOCKENS[1]].value) || std::stoi(VARIABLES[TOCKENS[3]].value)) {
		READ_MODE = CONDITION;
	}
	else {cnt_else_version();}
}


