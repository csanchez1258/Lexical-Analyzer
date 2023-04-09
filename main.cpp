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

  //for our program we needed to return a pair of two lists
  //one with the token and lexeme and one with the line number and file name
  //here we seperate each tokens to their own variable and pass it into the parser()
  auto tokenlist = token.first;
  auto tokeninfo = token.second;

  Display(tokenlist);

  std::cout << "\n\nNow Checking rules for Rat23s\n";
  std::cout << "===============================\n";
  parser(tokenlist, tokeninfo);

  std::cout << "\n\nend\n\n";

  return 0;
}
