#pragma once
void variable_create(std::string text);

void variable_create(std::string text) {
	std::string tockens[3];

	int index = 0;
	std::string toc = "";
	int toc_count = 0;
	for (int i = 0; i < text.length(); ++i) {
		if (text[i] == '(' || text[i] == ',' || text[i] == ' ' || text[i] == ')') {
			if (toc_count >= 3) { error("You can entered only 2 arguments"); }
			if (toc.length() != 0) {
				tockens[index++] = toc;
				toc = "";
				toc_count++;
			}
			continue;
		}
		toc += text[i];
	}

	// tockens conditional
	if (tockens[0] == "num") { // NUMBER type
		try {
			if (!NUMB_TYPE.count(tockens[1])) {
				NUMB_TYPE[tockens[1]] = std::stoi(tockens[2]);
			}
			else {
				error("Variable name can was only one");
			}
		}
		catch (const std::exception&) {
			error("Variable value is not a number");
		}

	}
	else

	if (tockens[0] == "str") { // STRING type
		if (!STRING_TYPE.count(tockens[1])) {
			if (tockens[2].length() == 0) { warning("argument is not indentified"); }
			STRING_TYPE[tockens[1]] = tockens[2];
		}
		else {
			error("Variable name can was only one");
		}
	}
	else

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
