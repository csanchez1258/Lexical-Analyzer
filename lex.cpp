#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

#include "lex.h"

std::vector<std::string> keyword{"while", "if", "else", "for", "print", "endwhile"};
std::vector<std::string> identifier{"int", "string", "fahr"};
std::vector<std::string> opertr{"+", "-", "/", "%", "<=", "==", ">=", "<", ">", "=", "*"};
std::vector<std::string> seperator{"{", "}", "(", ")", "[", "]", ",", ";", ":", "#"};

enum FSM_TRANSITION
{
  REJECT = 0,
  INTEGER,
  REAL,
  IDENTIFER,
  UNKNOWN
};

int stateTable[][5] = {{0, INTEGER, REAL, IDENTIFER, UNKNOWN},
                       /* STATE 1: INTEGER */ {INTEGER, INTEGER, REAL, UNKNOWN, REJECT},
                       /* STATE 2: REAL */ {REAL, REAL, UNKNOWN, UNKNOWN, REJECT},
                       /* STATE 3: IDENTIFER */ {IDENTIFER, IDENTIFER, UNKNOWN, IDENTIFER, REJECT},
                       /* STATE 4: UNKOWN */ {UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN}};
std::vector<std::pair<std::string, std::string>>
Lexer(const std::string &filename)
{
  std::ifstream fin(filename, std::ios::binary); // open file
  std::vector<std::pair<std::string, std::string>> ready;
  std::string buffer; // buffer
  std::string tokens;
  int col = REJECT;
  int current_state = REJECT;
  int prevState = REJECT;
  if (fin.is_open())
  {
    while (fin >> buffer)
    {
      // convert the buffer into a string and save it to the class variable
      // std::cout << "READING BUFFER: " << buffer << '\n';
      buffer += " ";
      // std::cout << "READING TOKENS: " << tokens << '\n';
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
  // std::cout << "BUFFER: " << tokens << '\n';
  //  start parsing the vector
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
      // std::cout << "Added: " << temp << '\n';
    }
    col = Get_FSM_Col(*i);
    //std::cout << "Current char: " << *i << "\nCurrent Coumn: " << col << "\n\n";
    //std::cout << "Current state: " << current_state << '\n';
    //std::cout << "FSM state: " << stateTable[current_state][col] << "\n\n";
    // get the cuurent state
    current_state = stateTable[current_state][col];
    //std::cout << "UPDATED state: " << current_state << "\n\n";

    std::string possible_op_sep(1, *i);
    std::string next_sep_op(1, *std::next(i, 1));
    //std::cout << "TEMP TOP: " << temp << '\n';
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
      //std::cout << "\n\nFOUND SEP: " << *i << "\n\n";
      std::string s(1, *i);
      ready.push_back(std::make_pair(s, "SEPERATOR"));
      temp.clear();
      current_state = 0;
      continue;
    }
    else if (isOperator(possible_op_sep))
    {
      // add to check next op
      // std::cout << "\n\nFOUND OP: " << *i << "\n\n";
      if (*(std::next(i, 1)) == '=')
      {
        // std::cout << "Continuing\n";
        current_state = 0;
        continue;
      }
      std::string s(1, *i);
      // std::cout << "PUSHING: " << temp << '\n';
      ready.push_back(std::make_pair(temp, "OPERATOR"));
      temp.clear();
      current_state = 0;
      continue;
    }

    else if (isKeyword(temp))
    {
      //std::cout << "\n\nFOUND Keyword: " << temp << "\n\n";
      ready.push_back(std::make_pair(temp, "KEYWORD   "));
      temp.clear();
      current_state = 0;
      continue;
    }
    else
    {
      if (current_state == REJECT || *std::next(i, 1) == ' ' || isSeperator(next_sep_op) || isOperator(next_sep_op))
      {
        //std::cout << "PUSHING STATE: " << prevState << '\n';
        //std::cout << "CURRENT TEMP: " << temp << '\n';
        ready.push_back(std::make_pair(temp, LexName(prevState)));
        temp.clear();
        continue;
      }
      //  else
      //  {
      //  temp += *i;
      //  std::cout << "TEMP: " << temp << '\n';
      //  }
      prevState = current_state;
      //std::cout << "prevval: " << prevState << '\n';
    }
  }

  return ready;
}

int Get_FSM_Col(char currentChar)
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
    return "REAL  ";
    break;
  case IDENTIFER:
    return "IDENTIFER";
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

bool isReal(const std::string &token)
{
  std::istringstream buffer(token);
  float f;
  buffer >> std::noskipws >> f; // noskipws considers leading whitespace invalid
  // Check the entire string was consumed and if either failbit or badbit is set
  return buffer.eof() && !buffer.fail();
}
