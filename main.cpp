#include <iostream>

#include "lex.h"

int main() {

  Lexical foo;
  foo.ReadCode("code.txt");

  std::cout << "Read code successfully!\n";

  foo.Display();

  return 0;
}
