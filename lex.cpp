#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

#include "lex.h"

std::vector<std::string> keyword {"while", "if", "else", "for", "print", "endwhile"};
std::vector<std::string> identifier{"int", "string", "fahr"};
std::vector<std::string> opertr{"+", "-", "/", "%", "<=", "==", ">=", "<", ">", "="};
std::vector<std::string> seperator{"{", "}", "(", ")", "[", "]", "<", ">", ",", ";", ":", "*", "#"};

std::string Lexer(const std::string &filename)
{
  std::ifstream fin(filename, std::ios::binary);  //open file
  std::vector<std::pair<std::string, std::string>> ready;
  std::string buffer; // buffer
  std::string tokens;
  if (fin.is_open())
  {
    while(!(fin.eof()))
    {
      fin >> buffer; // convert the buffer into a string and save it to the class variable
      buffer += " ";
      tokens += buffer;
    }
  }
  else
  {
   std::cout << "unable to open file.\n";
   return tokens;
  }
  fin.close();
  std::string temp;
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
    std::cout << "Added: " << temp << '\n';
   }
   std::string possible_op_sep(1, *i);
   std::cout << "POSSIBLE: " << possible_op_sep << '\n';


   if (isSeperator(possible_op_sep))
   {
      //add to check next op
      std::cout << "\n\nFOUND SEP: " << *i << "\n\n";
      std::string s(1, *i);
      ready.push_back(std::make_pair(s, "SEP"));
      temp.clear();
   }
   else if (isOperator(possible_op_sep))
   {
      //add to check next op
      std::cout << "\n\nFOUND OP: " << *i << "\n\n";
      std::string s(1, *i);
      ready.push_back(std::make_pair(s, "OPERATOR"));
      temp.clear();
   }
   else if (isKeyword(temp))
   {
      std::cout << "\n\nFOUND Keyword: " << temp << "\n\n";
      ready.push_back(std::make_pair(temp, "KEYWORD"));
      temp.clear();
   }
   else if (!(isdigit(temp[0])) && *(std::next(i, 1)) == ' ')
   {
      std::cout << "\n\nFOUND IDENTIFIER: " << temp << "\n\n";
      ready.push_back(std::make_pair(temp, "KEYWORD"));
      temp.clear();
   }
   //std::cout << temp;
  }

  return tokens;
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
