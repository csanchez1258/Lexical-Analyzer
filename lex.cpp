#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

#include "lex.h"

std::vector<std::string> keyword{
    "while",
    "if",
    "else",
    "for",
    "print",
    "endwhile",
    "int",
    "string",
    "float",
    "bool",
    "true",
    "false",
};
std::vector<std::string> opertr{"+", "-", "/", "%", "<=", "==", ">=", "<", ">", "=", "*"};
std::vector<std::string> seperator{"{", "}", "(", ")", "[", "]", ",", ";", ":", "#", "\"", "\"", "\'"};

enum FSM_TRANSITION
{
  REJECT = 0,
  INTEGER,
  REAL,
  IDENTIFER,
  UNKNOWN
};
//CREATE A TABLE OF OUR TRANSITIONs
int state_table[][5] =                         {{0, INTEGER, REAL, IDENTIFER, UNKNOWN},
                       /* STATE 1: INTEGER */   {INTEGER, INTEGER, REAL, UNKNOWN, REJECT},
                       /* STATE 2: REAL */      {REAL, REAL, UNKNOWN, UNKNOWN, REJECT},
                       /* STATE 3: IDENTIFER */ {IDENTIFER, IDENTIFER, UNKNOWN, IDENTIFER, REJECT},
                       /* STATE 4: UNKOWN */    {UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN}};
std::vector<std::pair<std::string, std::string>> Lexer(const std::string &filename)
{
  std::ifstream fin(filename, std::ios::binary); // open file
  std::vector<std::pair<std::string, std::string>> ready;
  std::string buffer; // buffer
  std::string tokens;
  int col = REJECT;
  int current_state = REJECT;
  //start reading the file
  if (fin.is_open())
  {
    while (fin >> buffer)
    {
      buffer += " ";
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
  //  start traversing the vector
  for (auto i = tokens.begin(); i != tokens.end(); i++)
  {
    if (*i == ' ')
    {
      temp.clear();
      continue;
    }
    else
    {
      temp += *i;
    }
    //grab the num of column for current char
    col = FSM_COLM(*i);

    //upadate state by looking at the state_table and transition
    current_state = state_table[current_state][col];


    //for the seperators, operaters, and keywords
    //we will not need FSM so we will do simple approach
    std::string possible_op_sep(1, *i);
    std::string next_sep_op(1, *std::next(i, 1));

    //check for comments
    if (possible_op_sep == "[" && next_sep_op == "*")
    {
      auto commentEnd = std::find(i, tokens.end(), ']');
      i = commentEnd;
      current_state = 0;
      continue;
    }

    if (isSeperator(possible_op_sep))
    {
      // add to check next op
      std::string s(1, *i);
      ready.push_back(std::make_pair(s, "SEPERATOR"));
      temp.clear();
      current_state = 0;
      continue;
    }
    else if (isOperator(possible_op_sep))
    {
      // add to check next op
      if (*(std::next(i, 1)) == '=')
      {
        current_state = 0;
        continue;
      }
      std::string s(1, *i);
      ready.push_back(std::make_pair(temp, "OPERATOR"));
      temp.clear();
      current_state = 0;
      continue;
    }

    else if (isKeyword(temp))
    {
      ready.push_back(std::make_pair(temp, "KEYWORD"));
      temp.clear();
      current_state = 0;
      continue;
    }

    //if we did not pass our simple checks for ops, seps, and keys, then check for
    //identfiers, real, and int using FSM transitions
    else
    {
      if (current_state == REJECT || *std::next(i, 1) == ' ' || isSeperator(next_sep_op) || isOperator(next_sep_op))
      {
        ready.push_back(std::make_pair(temp, LexName(current_state)));
        temp.clear();
        continue;
      }
    }
  }

  return ready;
}

int FSM_COLM(char currentChar)
{
  // check for integer numbers
  if (isdigit(currentChar))
  {
    return INTEGER;
  }

  // check for real numbers
  else if (currentChar == '.')
  {
    return REAL;
  }

  // check for characters
  else if (isalpha(currentChar) || currentChar == '_')
  {
    return IDENTIFER;
  }

  return UNKNOWN;
}

std::string LexName(int lexeme)
{
  switch (lexeme)
  {
  case INTEGER:
    return "INTEGER";
    break;
  case REAL:
    return "REAL";
    break;
  case IDENTIFER:
    return "IDENTIFIER";
    break;
  case UNKNOWN:
    return "UNKNOWN";
    break;
  default:
    return "ERROR";
    break;
  }
}

bool isSeperator(const std::string &token)
{
  if (std::find(seperator.begin(), seperator.end(), token) != seperator.end())
  {
    return true;
  }
  else
    return false;
}

bool isOperator(const std::string &token)
{
  if (std::find(opertr.begin(), opertr.end(), token) != opertr.end())
  {
    return true;
  }
  else
    return false;
}

bool isKeyword(const std::string &token)
{
  if (std::find(keyword.begin(), keyword.end(), token) != keyword.end())
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

void Display(const std::vector<std::pair<std::string, std::string>> &ready)
{
  std::cout << "Token" << std::setw(45) << "Lexi" << '\n'
            << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

  for (const auto &i : ready)
  {

    if (i.second == "KEYWORD")
    {
      std::cout << i.second << std::setw(43) << i.first << '\n';
    }
    else if (i.second == "OPERATOR")
    {
      std::cout << i.second << std::setw(42) << i.first << '\n';
    }
    else if (i.second == "SEPERATOR")
    {
      std::cout << i.second << std::setw(41) << i.first << '\n';
    }
    else if (i.second == "IDENTIFIER")
    {
      std::cout << i.second << std::setw(40) << i.first << '\n';
    }
    else if (i.second == "REAL")
    {
      std::cout << i.second << std::setw(46) << i.first << '\n';
    }
    else if (i.second == "INTEGER")
    {
      std::cout << i.second << std::setw(43) << i.first << '\n';
    }
    else if (i.second == "UNKNOWN")
    {
      std::cout << i.second << std::setw(43) << i.first << '\n';
    }
    else
    {
      std::cout << "ERROR: Unknown RETURN VALUE\n";
    }
  }
}
