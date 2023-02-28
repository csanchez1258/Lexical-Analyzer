#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "lex.h"


int main() {

  auto token = Lexer("code.txt");

  std::cout << "\n";

  Display(token);

  std::cout << "\n";

  return 0;
}
