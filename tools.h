#pragma once

template<typename T>
void w(T t) {
	std::cout << t;
	/*
	color_set(8);
	std::cout << " (" << line_pointer << " line)";
	color_set(15);
	*/
	std::cout << "\n";
}

void first_white_space_del() {
	while (CODE_LINE[0] == '\t' || CODE_LINE[0] == ' ') {
		CODE_LINE.erase(0, 1);
	}
}

bool var_found(std::string var) {
	return VARIABLES.count(var);
}

void GNL() {// Get Next Line
	std::getline(CODE, CODE_LINE);
	line_pointer++;

	first_white_space_del();
	get_tockens();
}

void color_set(int color) {
	/*HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, color);*/
}

void error(std::string msg) {
	color_set(124); // red in white
	std::cout << " ERROR ";
	color_set(79); // white in red
	std::cout << " in " <<  line_pointer << " line: " << msg << " " << std::endl;
	color_set(15); // white in black
	exit(0);
}

void warning(std::string msg) {
	color_set(142); // yellow in gray
	std::cout << " WARNING ";
	color_set(232); // gray in yellow
	std::cout << " in " << line_pointer << " line: " << msg << " " << std::endl;
	color_set(15); // white in black
}

void tockens_reset() {
	for (int i = 0; i < max_tocken_conunt; ++i) {
		TOCKENS[i] = "";
	}
}

void tockens_show() {
	color_set(5);
	w("_________");
	for (int i = 0; i < max_tocken_conunt; ++i) {
		w(TOCKENS[i]);
	}
}

void get_string(int i) {
	if (CODE_LINE[i] == '\'') {
		i++;
		while (CODE_LINE[i] != '\'') {
			TOCKENS[2] += CODE_LINE[i++];
		}
	}
	else if(CODE_LINE[i] >= 65 && CODE_LINE[i] <= 90 || CODE_LINE[i] >= 97 && CODE_LINE[i] <= 122){
		while (CODE_LINE[i] != ';') {
			TOCKENS[2] += CODE_LINE[i++];
		}

		if (var_found(TOCKENS[2])) {
			if (VARIABLES[TOCKENS[2]].type != "str") {
				error("reference variable type is not equal for \"" + TOCKENS[1] + "\" type");
			}
			TOCKENS[2] = VARIABLES[TOCKENS[2]].value;
		}
		else {
			error("this variable is not found");
		}
	}
	else {
		error("variable keywork first char can was char");
	}
}

void get_output_value(int i) {
	if(CODE_LINE[i] == '\'') {
		std::string tmp;
		i++;
		while (CODE_LINE[i] != '\'') {
			TOCKENS[1] += CODE_LINE[i++];
		}
		return;
	}

	while (CODE_LINE[i] != ';') {
		TOCKENS[1] += CODE_LINE[i++];
	}
	
	if (TOCKENS[1] == "true" || TOCKENS[1] == "false" || 
			TOCKENS[1][0] >= 48 && TOCKENS[1][0] <= 57) {
		return;
	}

	if (var_found(TOCKENS[1])) {
		TOCKENS[1] = VARIABLES[TOCKENS[1]].value;
	}
	else {
		error("variable isn't exists");
	}
}

void get_tockens() {
	std::string fk;
	int index = 0;

	tockens_reset();

	for (int i = 0; i < CODE_LINE.length(); ++i) {
		if (index >= max_tocken_conunt) {error("Max tockens is 5");}
		
		if(TOCKENS[0] == "str") {
			if (index == 2) {
				get_string(i);
				break;
			}
		}

		if (TOCKENS[0] == "output") {
			get_output_value(i);
			break;
		}

		if (CODE_LINE[i] == ' ' || CODE_LINE[i] == ';') {
			TOCKENS[index] = fk;
			fk = "";
			index++;
			continue;
		}
		fk += CODE_LINE[i];
	}
}
