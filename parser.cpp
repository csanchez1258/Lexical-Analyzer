#include <iostream>
#include <vector>
#include <stack>
#include "parser.h"

void parser(const std::vector<std::pair<std::string, std::string>> &tokens)
{

  std::stack<std::pair<std::string, std::string>> lextokens;

  for(auto const &t : tokens)
  {
    //std::cout << t.first << " " << t.second;
    lextokens.push(t);
  }

  //now that we have all the tokens in a stack lets read one by one and checking each rule

  while(!lextokens.empty())
  {
    rat23s(lextokens);
    opt_functions(lextokens);;
    function_def(lextokens);
    function(lextokens);
    ids(lextokens);
  }

  // std::cout << "Printing tokens from the parser ..." << std::endl;

  // while(!lextokens.empty())
  // {
  //   auto temp = lextokens.top();
  //   std::cout << temp.first << " " << temp.second << std::endl;
  //   lextokens.pop();
  // }

  // rat23s(&tokens);
}

// void rat23s(auto const &tokens)
// {
//   opt_functions();
//   if (token = "#")
//   {
//     lexer();
//   }
// }

// void opt_functions(auto const &tokens)
// {
//   function_def();
// }

// void function_def(auto const &tokens)
// {
//   function();
// }

// void function(auto const &tokens)
// {
//   //function then identifier (<opt parameter list>) <opt decl list> <Body>
// }

// void ids(auto const &tokens)
// {

// }
