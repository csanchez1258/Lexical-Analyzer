#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "lex.h"
#include "parser.h"


int main() {

  std::string fname;

  std::cout << "Enter file name: ";
  std::cin >> fname;
  std::cout << std::endl;

  auto token = Lexer(fname);

  Display(token);

  std::cout << "\n\nNow Checking rules for Rat23s\n";
  std::cout << "===============================\n";
  parser(token);

  std::cout << "\n\nend\n\n";

  // std::cout << "\n";

  // Display(token);

  // std::cout << "\n";

  return 0;
}
