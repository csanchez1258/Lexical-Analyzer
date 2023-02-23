#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "lex.h"


int main() {

  auto token = Lexer("code.txt");

  std::cout << "\n\n\n\n\n\n\n\n";

  for (const auto &i : token)
  {
    std::cout << std::left  << i.first << std::setw(40) << std::right << i.second << '\n';
  }
  return 0;
}
