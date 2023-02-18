#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


    void Display();
    std::vector<std::string> Tokenize(const std::string &filename);
    bool isKeyword(const std::string &token);
    bool isOperator(const std::string & token);
    bool isSeperator(const char &token);
