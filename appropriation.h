#pragma once
void opr_sum_str() {
	std::string tmp = "'";
	VARIABLES[TOCKENS[0]].value = tmp + TOCKENS[2] + TOCKENS[4] + tmp;
}

void opr_apostrov_clear(int i) {
	if (TOCKENS[i][0] == '\'') {
		TOCKENS[i].erase(0, 1);
		TOCKENS[i].erase(TOCKENS[i].length() - 1, 1);
	}
	else {
		if (var_found(TOCKENS[i])) {
			TOCKENS[i] = VARIABLES[TOCKENS[i]].value;
		}
		else {
			error("variable is not found");
		}
	}
}

int translate_num(int i) {
	if (var_found(TOCKENS[i])) {
		TOCKENS[i] = VARIABLES[TOCKENS[i]].value;
	}

	if (TOCKENS[i][0] >= 48 && TOCKENS[i][0] <= 57) {
		return std::stoi(TOCKENS[i]);
	}

	error("it's not a number");
}

void operators() {
	const std::string op = TOCKENS[3];
	const std::string type = VARIABLES[TOCKENS[0]].type;

	if (type == "str") {
		for (int i = 2; i <= 4; i += 2) {
			opr_apostrov_clear(i);
		}
		if (op == "+") { opr_sum_str(); }
		else
		error(op + " can't worked with string types");
	}
	else {
		int num_1 = translate_num(2);
		int num_2 = translate_num(4);
		int res{};

		if (op == "+") { res = num_1 + num_2; } else
		if (op == "-") { res = num_1 - num_2; }else
		if (op == "*") { res = num_1 * num_2; }else
		if (op == "*") { res = num_1 * num_2; }else
		if (op == "/") { res = num_1 / num_2; }else
		if (op == "%") { res = num_1 * num_2; }else
		error("undefined operator");

		std::ostringstream oss;
		oss << res;
		VARIABLES[TOCKENS[0]].value = oss.str();
	}
}

void just_appropriation() {
	const std::string type = get_var_type(0);
	const std::string type_2 = get_var_type(2);
	if (type != type_2) {
		error("variables types is not equal");
	}
	if (type == "str") {
		opr_apostrov_clear(2);
		std::string tmp = "'";
		VARIABLES[TOCKENS[0]].value = tmp + TOCKENS[2] + tmp;
	}
	if (type == "bool") {
		if (TOCKENS[2] == "flase" || TOCKENS[2] == "true") {
			VARIABLES[TOCKENS[0]].value = TOCKENS[2];
		}
		else {
			error("bool type variable cant get other type");
		}
	}
	
	if (type == "num") {
		for (int i = 0; i < TOCKENS[2].length(); ++i) {
			if (TOCKENS[i][0] < 48 && TOCKENS[i][0] > 57) {
				error("this can only have number type");
			}
		}

		VARIABLES[TOCKENS[0]].value = TOCKENS[2];
	}
	else {
		error("undefined error");
	}
}

void appropriation() {
	const std::string var_type = get_var_type(0); //TOCKENS[0]
	const std::string var_type_2 = get_var_type(2);

	if(TOCKENS[1] != "=") { error("undefined symbol"); }
	
	if (TOCKENS[3] != "") {
		const std::string var_type_4 = get_var_type(4);
	
		if (var_type != var_type_2 && var_type != var_type_4) {
			error("different variable types");
		}
		
		operators(); //TOCKENS[3]
	}
	else {
		if (var_type != var_type_2) {
			error("different variable types");
		}
		just_appropriation();
	}
}
