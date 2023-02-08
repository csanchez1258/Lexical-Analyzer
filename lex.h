#pragma once

#include <iostream>
#include <fstream>
#include <string>

class Lexical
{
  public:
    void Display();
    void ReadCode(const std::string & filename);

  private:
    std::string code;
};
