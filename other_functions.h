#pragma once
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
	if (first_keyword == "num" || first_keyword == "str" || first_keyword == "bool") { create_var(); }
	else
	if (first_keyword == "if") { condition(); }
	else
	if (first_keyword == "for") { READ_MODE = SKIP; /* �������� */ }
	else
	if (first_keyword == "else") { READ_MODE = SKIP; }
	else
	if (first_keyword == "output") {}
	else { error("syntax error"); }
	}
	else {
		// ���������� 
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