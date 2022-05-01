#include "system_includes.h"

enum mods { DEFAULT, CYCLE, CONDITION, SKIP };

struct Var {
	std::string type;
	std::string value;
};

const int max_tocken_conunt = 5;
std::fstream CODE("variables.cpk"); // path for programm code file
std::string TOCKENS[max_tocken_conunt]; // every line devided in tockens
std::string CODE_LINE; // get new line 
std::map<std::string, Var> VARIABLES; // all variables with their value and type
int line_pointer = 0; // for easy errors show line
mods READ_MODE = DEFAULT; 

#include "local_includes.h"

int main() {
	line_read();
}