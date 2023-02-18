#include <iostream>
#include <vector>
#include <string>
#include "lex.h"

int main() {

  std::vector<std::string> token;

  token = Tokenize("code.txt");

  for(auto i : token)
  {
    std::cout << i << '\n';
  }

  return 0;
}
