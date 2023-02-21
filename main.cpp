#include <iostream>
#include <vector>
#include <string>
#include "lex.h"

int main() {

  auto token = Lexer("code.txt");

  // for(auto i : token)
  // {
  //   std::cout << i.first << "    " << i.second;
  // }
  return 0;
}
