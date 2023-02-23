#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "lex.h"


int main() {

  auto token = Lexer("code.txt");

  std::cout << "\n\n\n\n\n\n\n\n";

  std::cout << "Token" << std::setw(40) << "Lexi" << '\n'
              << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";

  for (const auto &i : token)
  {

    
    std::cout << std::left  << i.second << std::setw(35) << std::right << i.first << '\n';
  }
  return 0;
}
