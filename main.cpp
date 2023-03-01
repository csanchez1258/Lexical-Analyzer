#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "lex.h"


int main() {

  std::string fname;

  std::cout << "Enter file name: ";
  std::cin >> fname;
  std::cout << std::endl;

  auto token = Lexer(fname);

  std::cout << "\n";

  Display(token);

  std::cout << "\n";

  return 0;
}
