#pragma once

//TOOLS
template<typename T>
void w(T t);
void first_white_space_del();
bool var_found(std::string var);
void GNL();
void color_set(int color);
void error(std::string msg);
void warning(std::string msg);
void tockens_reset();
void tockens_show();
void get_string(int i);
void get_tockens();

// CONDITION
void cnt_else_version();
void cnt_type_equal(std::string type);
void cnt_big();
void cnt_small();
void cnt_equal();
void cnt_not_equal();
void cnt_and();
void cnt_or();
void cnt_opeartors(std::string opr);
void condition();

//OTHER FUNCTIONS
void create_var();
void default_mode();
void cycle_mode();
void condition_mode();
void skip_mode();
void line_read();

//INCLUDES ALL FILES
#include "tools.h"
#include "condition.h"
#include "other_functions.h"