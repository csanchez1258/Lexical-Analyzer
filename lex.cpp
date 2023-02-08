#include <iostream>
#include <iomanip>

#include "lex.h"


void Lexical::Display()
{
  std::cout << "Your code is: \n";
  std::cout << "===================================\n";
  std::cout << code;
}

void Lexical::ReadCode(const std::string & filename) {
  std::ifstream fin(filename, std::ios::binary);  //open file
  std::stringstream buffer;                       //buffer
  if (fin.is_open())
  {
    std::cout << "opening file...\n";
    buffer << fin.rdbuf();                        //read the file buffer and store it

    code = buffer.str();                          //convert the buffer into a string and save it to the class variable
  }
  else
  {
   std::cout << "unable to open file.\n";
   return;
  }
  fin.close();
}
