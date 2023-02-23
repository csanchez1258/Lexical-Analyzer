#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


    void Display();
    std::vector<std::pair<std::string, std::string>> Lexer(const std::string &filename);
    bool isKeyword(const std::string &token);
    bool isOperator(const std::string & token);
    bool isSeperator(const std::string & token);
    std::string toString(char token);
    bool isReal(const std::string &token);
