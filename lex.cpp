#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>

#include "lex.h"

std::vector<std::string> keyword {"while", "if", "else", "for", "print", "endwhile"};
std::vector<std::string> identifier{"int", "string", "fahr"};
std::vector<std::string> opertr{"+", "-", "/", "%", "<=", "==", ">=", "<", ">", "=", "*"};
std::vector<std::string> seperator{"{", "}", "(", ")", "[", "]", ",", ";", ":", "#"};

std::vector<std::pair<std::string, std::string>> Lexer(const std::string &filename)
{
  std::ifstream fin(filename, std::ios::binary);  //open file
  std::vector<std::pair<std::string, std::string>> ready;
  std::string buffer; // buffer
  std::string tokens;
  if (fin.is_open())
  {
    while(fin >> buffer)
    {
       // convert the buffer into a string and save it to the class variable
      //std::cout << "READING BUFFER: " << buffer << '\n';
      buffer += " ";
      //std::cout << "READING TOKENS: " << tokens << '\n';
      tokens += buffer;
    }
  }
  else
  {
   std::cout << "unable to open file.\n";
   return ready;
  }
  fin.close();
  std::string temp;
  //std::cout << "BUFFER: " << tokens << '\n';
  // start parsing the vector
  for(auto i = tokens.begin(); i != tokens.end(); i++)
  {
   if (*i == ' ')
   {
      temp.clear();
   }
   else
   {
    temp += *i;
    //std::cout << "Added: " << temp << '\n';
   }
   std::string possible_op_sep(1, *i);
   std::string next_sep_op(1, *std::next(i, 1));
   //std::cout << "NEXT SEP: " << next_sep_op << '\n';
   //std::cout << "POSSIBLE: " << possible_op_sep << '\n';

   if(possible_op_sep == " ")
   {
      continue;
   }

   if (isSeperator(possible_op_sep) )
   {
      //add to check next op
     // std::cout << "\n\nFOUND SEP: " << *i << "\n\n";
      std::string s(1, *i);
      ready.push_back(std::make_pair(s, "SEPERATOR"));
      temp.clear();
   }
   else if (isOperator(possible_op_sep))
   {
      //add to check next op
      //std::cout << "\n\nFOUND OP: " << *i << "\n\n";
      if(*(std::next(i, 1)) == '=')
      {
        //std::cout << "Continuing\n";
        continue;
      }
      std::string s(1, *i);
     //std::cout << "PUSHING: " << temp << '\n';
      ready.push_back(std::make_pair(s, "OPERATOR"));
      temp.clear();
   }
   else if (isKeyword(temp))
   {
     // std::cout << "\n\nFOUND Keyword: " << temp << "\n\n";
      ready.push_back(std::make_pair(temp, "KEYWORD"));
      temp.clear();
   }
   else if(isReal(temp) && !isdigit(*std::next(i, 1)) && *std::next(i,1) != '.')
   {
     // std::cout << "\n\nFOUND Real: " << temp << "\n\n";
      ready.push_back(std::make_pair(temp, "REAL"));
      temp.clear();
   }
   else if ((!(isdigit(temp[0])) && *(std::next(i, 1)) == ' ') || ( isSeperator(next_sep_op) || isOperator(next_sep_op)))
   {
      //std::cout << "\n\nFOUND IDENTIFIER: " << temp << "\n\n";
      ready.push_back(std::make_pair(temp, "IDENTIFIER"));
      temp.clear();
   }
   //std::cout << temp;
  }

  return ready;
}

bool isSeperator(const std::string &token)
{
  if(std::find(seperator.begin(), seperator.end(), token) != seperator.end())
  {
   return true;
  }
  else
   return false;
}

bool isOperator(const std::string & token)
{
  if(std::find(opertr.begin(), opertr.end(), token) != opertr.end())
  {
   return true;
  }
  else
   return false;
}

bool isKeyword(const std::string & token)
{
  if(std::find(keyword.begin(), keyword.end(), token) != keyword.end())
  {
   return true;
  }
  else
   return false;
}

std::string toString(char token)
{
  std::string temp(1, token);
  return temp;
}

bool isReal(const std::string &token)
{
  std::istringstream buffer(token);
  float f;
  buffer >> std::noskipws >> f; // noskipws considers leading whitespace invalid
  // Check the entire string was consumed and if either failbit or badbit is set
  return buffer.eof() && !buffer.fail();

}
