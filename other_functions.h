#pragma once
void create_var() {
	if (var_found(TOCKENS[1])) {
		error("this name is exists");
	}
	
	if (TOCKENS[1] == "num" || TOCKENS[1] == "bool" ||
			TOCKENS[1] == "str" || TOCKENS[1] == "for" ||
			TOCKENS[1] == "output" || TOCKENS[1] == "else" ||
			TOCKENS[1] == "if") {
		error("\"" + TOCKENS[1] + "\" name is reserved. You can't use this name for variables");
	}

	if (TOCKENS[0] == "num") {
		for (int i = 0; i < TOCKENS[2].length(); ++i) {
			if (TOCKENS[2][i] >= 48 && TOCKENS[2][i] <= 57 || TOCKENS[2][i] == '-') {
				continue;
			}
			error("you can't appropriate \"" + TOCKENS[2] + "\" symbol for number type");
		}
	}

	VARIABLES[TOCKENS[1]] = { TOCKENS[0], TOCKENS[2] };
}

std::string get_var_type(int tocken_index) {
	if (TOCKENS[tocken_index][0] >= 48 && TOCKENS[tocken_index][0] <= 57) {
		return "num";
	}
	if (var_found(TOCKENS[tocken_index]) && VARIABLES[TOCKENS[tocken_index]].type != "bool") {
		return VARIABLES[TOCKENS[tocken_index]].type;
	}
	else {
		if (tocken_index == 0) {
			error("this variable isn't create");
		}
		if (TOCKENS[tocken_index][0] == '\'') {
			return "str";
		}
		if (VARIABLES[TOCKENS[tocken_index]].type == "bool") {
			return "bool";
		}
		for (int i = 0; i < TOCKENS[tocken_index].length(); ++i) {
			if (TOCKENS[tocken_index][0] < 48 || TOCKENS[tocken_index][0] > 57) {
				error("undefined value type");
			}
		}
		return "num";
	}
}

void output() {
	if (TOCKENS[1] == "") {
		error("haven't argument");
	}
	w(TOCKENS[1]);
}

void for_keyword() {
	int for_count{};
	try{
		for_count = std::stoi(TOCKENS[1]);
		if (for_count < 0) {
			error("for number can't was small than 0");
		}
	}
	catch (const std::exception&){
		error("after for have only number");
	}

	std::map<int, std::string>for_body;

	GNL();
	int index = 0;
	while (CODE_LINE != "}") {
		for_body[index++] = CODE_LINE;
		GNL();
	}

	while (for_count != 0) {
		for (auto &i : for_body) {
			CODE_LINE = i.second;
			get_tockens();
			default_mode();
		}
		for_count--;
	}

}

void default_mode() {
	if (CODE_LINE.length() == 0) { return; }
	std::string first_keyword = TOCKENS[0];

	if (TOCKENS[1] != "=") {
		if (first_keyword == "num" || first_keyword == "str" || first_keyword == "bool") { create_var(); }else
		if (first_keyword == "if") { condition(); }else
		if (first_keyword == "for") { for_keyword(); } else
		if (first_keyword == "else") { READ_MODE = SKIP; } else
		if (first_keyword == "output") { output(); }
	}
	else { appropriation(); }
}

void skip_mode() {
	while (CODE_LINE != "}") { GNL(); }
	READ_MODE = DEFAULT;
}

void line_read() {
	while (!CODE.eof()) {
		GNL();

		switch (READ_MODE) {
			case DEFAULT: { default_mode(); break; }
			case SKIP: { skip_mode(); break; }
			case CONDITION: { condition_mode(); }
		}

	}
}
