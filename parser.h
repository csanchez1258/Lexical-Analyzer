#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void parser(const std::vector<std::pair<std::string, std::string>> &tokens);
void rat23s(const std::vector<std::pair<std::string, std::string>> &tokens);
void opt_functions(const std::vector<std::pair<std::string, std::string>> &tokens);
void function_def(const std::vector<std::pair<std::string, std::string>> &tokens);
void function(const std::vector<std::pair<std::string, std::string>> &tokens);
void ids(const std::vector<std::pair<std::string, std::string>> &tokens);
