#include <iostream>
#include <iomanip>
#include <vector>

#include "lex.h"

std::vector<std::string> Tokenize(const std::string & filename) {
  std::ifstream fin(filename, std::ios::binary);  //open file
  std::string buffer;                       //buffer
  std::vector<std::string> tokens;
  if (fin.is_open())
  {
    while(!(fin.eof()))
    {
      fin >> buffer; // convert the buffer into a string and save it to the class variable
      tokens.push_back(buffer);
    }
  }
  else
  {
   std::cout << "unable to open file.\n";
   return tokens;
  }
  fin.close();
  return tokens;
}
