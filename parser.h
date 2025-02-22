#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
std::pair<std::string, std::string> nexttk(int skip);
void scanner();
std::pair<std::string, std::string> nexttk(int step) ;
void parser(const std::vector<std::pair<std::string, std::string>> &tokens, const std::vector<std::pair<std::string, std::string>> &tokeninfo);
void rat23s();
void check();
void opt_functions();
void function_def();
void function_def2();
void function();
void opt_parameter_list();
void parameter_list();
void parameter_list2();
void parameter();
void qualifier();
void body();
void opt_declaration_list();
void declaration_list();
void declaration_list2();
void declaration();
void ids();
void ids2();
void statement_list();
void statement_list2();
void statement();
void compound();
void assign();
void if_rule();
void if_rule2();
void return_rule();
void return_rule2();
void print_rule();
void scan_rule();
void while_rule();
void condition();
void relop();
void expression();
void expression_prime();
void term();
void term_prime();
void factor();
void primary();
void primary2();
void identifier();
void integer();
void real();

void errorresult(std::string tokenresult, std::string type);

