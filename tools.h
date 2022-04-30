#pragma once

template<typename T>
void w(T t) {
	std::cout << t;
	color_set(8);
	std::cout << " (" << line_pointer << " line)\n";
	color_set(15);
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
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, color);
}

void error(std::string msg) {
	color_set(124);
	std::cout << " ERROR ";
	color_set(79);
	std::cout << " in " <<  line_pointer << " line: " << msg << " " << std::endl;
	color_set(15);
	exit(0);
}

void warning(std::string msg) {
	color_set(142);
	std::cout << " WARNING ";
	color_set(232);
	std::cout << " in " << line_pointer << " line: " << msg << " " << std::endl;
	color_set(15);
}

void tockens_reset() {
	for (int i = 0; i < 4; ++i) {
		TOCKENS[i] = "";
	}
}

void tockens_show() {
	w("=====");
	for (int i = 0; i < 4; ++i) {
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
				error("reference variable type is not equal for " + TOCKENS[1] + " type");
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

void get_tockens() {
	std::string fk;
	int index = 0;

	tockens_reset();

	for (int i = 0; i < CODE_LINE.length(); ++i) {
		if (index >= 4) {error("Max tockens is 4");}
		
		if(TOCKENS[0] == "str") {
			if (index == 2) {
				get_string(i);
				w(TOCKENS[2]);
				break;
			}
		}

		if (CODE_LINE[i] == ' ' || CODE_LINE[i] == ';') {
			TOCKENS[index] = fk;
			fk = "";
			index++;
			continue;
		}
		fk += CODE_LINE[i];
	}
	
	if (TOCKENS[3] != "" && TOCKENS[0] != "if") {
		error("last word is undefined");
	}
}
