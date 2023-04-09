#include <iostream>
#include <vector>
#include <stack>
#include "parser.h"

std::vector<std::pair<std::string, std::string>> tokensglobal;
std::vector<std::pair<std::string, std::string>> tokensinfoglobal;
std::pair<std::string, std::string> singletoken;
std::vector<std::pair<std::string, std::string>>::iterator it;
int count = 0;
int infoi = 0;


//Needed a new scanner fucntion to grab tokens one by one from our list of all tokens
void scanner()
{
  std::cout << "\n\n||   Token: " << (*it).second << "      Lexeme: " << (*it).first << " || \n";
  if(it+1 != tokensglobal.end())
  {
    singletoken = *(++it);
    ++infoi;
  }
}


//function to grab the next token without modifying our iterator
std::pair<std::string, std::string> nexttk(int step) 
{
  auto next_token = *(it + step);
  return next_token;
}

//this parser will begin all rule check by calling rat23s()
void parser(const std::vector<std::pair<std::string, std::string>> &tokens, const std::vector<std::pair<std::string, std::string>> &tokeninfo)
{
  //set global variables to tokens and tokeninfo
  tokensglobal = tokens;
  tokensinfoglobal = tokeninfo;
  it = tokensglobal.begin();
  singletoken = *it;
  rat23s();
}


//rat23s() will begin all rule checks for a single token and continue on the chain of rules.
void rat23s()
{
  // if (switch) 
  std::cout << "<Rat23S> -> <Opt Function Definitions> # <Opt Declaration List> # <Statement List>\n";
  opt_functions();
  if (singletoken.first == "#") 
    scanner();
  else 
  {
    std::cout << "Expected #\n"; 
    errorresult(singletoken.first, "#");
  }

  opt_declaration_list();

  if (singletoken.first == "#") 
    scanner();
  else
  {
    std::cout << "Expected #\n";
    errorresult(singletoken.first, "#");
  }

  statement_list();
}

void opt_functions()
{
  std::cout << "<Opt Function Definitions> -> ";
  if(singletoken.first == "function")
  {
    std::cout << "<Function Definitions>\n";
    //scanner();
    function_def();
  }
  else
  {
    std::cout << "<Empty>\n";
  }
}

void function_def()
{
  std::cout << "<Function Definitions> -> <Function> <FunctionDefintion2>>\n";
  function();
  function_def2();
}

void function_def2()
{
  std::cout << "<Function 2> -> ";
  if(singletoken.first == "function")
  {
    std::cout << "<Function_Definitions>\n";
    function_def();
  }
  else
  {
    std::cout << "<Empty>";
  }
}

void function()
{
  //function then identifier (<opt parameter list>) <opt decl list> <Body>
  std::cout << "<Function> -> function <Identifier> ( <Opt Parameter List> ) <Opt Declaration List> <Body>\n";
  if(singletoken.first == "function")
  {
    scanner();
  }
  else
  {
    errorresult(singletoken.first, "function");
  }
  // std::cout << "\n\nBruh 5\n\n";
  identifier();
  if(singletoken.first == "(")
  {
    scanner();
  }
  else
  {
    errorresult(singletoken.first, "(");
  }
  opt_parameter_list();
  if(singletoken.first == ")")
    scanner();
  else
  {
    std::cout << "Expected a )";
    errorresult(singletoken.first, ")");
  }
  opt_declaration_list();
  body();
}

void opt_parameter_list()
{
  std::cout << "<Opt Parameter List> -> ";
  // std::cout << "\t\b\n\n\n\n HERE:: " << nexttk(1).first << '\n';
  if(nexttk(1).first != ")")
  {
    std::cout << "<Parameter List>\n";
    parameter_list();
  }
  else
  {
    std::cout << "<EMPTY>\n";
  }
}

void parameter_list()
{
  std::cout << "<Parameter List> ::= <Parameter> <Parameter List2>\n";
  parameter();
  parameter_list2();
}

void parameter_list2()
{
  std::cout << "<Parameter List 2> ->";
  if (singletoken.first == ",")
  {
    std::cout << ", <Parameter_List>\n";
    scanner();
    parameter_list();
  }
  else{
    std::cout << "<EMPTY>\n";
  }
}

void parameter()
{
  std::cout << "<Parameter> -> <IDs > <Qualifier>\n";
  ids();
  qualifier();
}

void qualifier()
{
  std::cout << "<Qualifier> -> ";
  if (singletoken.first == "int") 
  {
    std::cout << "int\n";
    scanner();
  }
  else if(singletoken.first == "bool")
  {
    std::cout << "bool\n";
    scanner();
  }
  else if(singletoken.first == "real")
  {
    std::cout << "real\n";
    scanner();
  }
  else
  {
    std::cout << "Expected a INT, REAL, or BOOL\n FOR: " << singletoken.first;
    errorresult(singletoken.first, "INT, REAL, or BOOL");
  }
}

void body()
{
  std::cout << "<Body> -> {<Statement List>}";
  if(singletoken.first == "{")
  {
    scanner();
    statement_list();
    if(singletoken.first == "}")
    {
      scanner();
    }
    else
    {
      std::cout << "Expected a }\n";
      errorresult(singletoken.first, "}");
    }
  }
  else
  {
    std::cout << "expected a {\n";
    errorresult(singletoken.first, "{");
  }
}

void opt_declaration_list()
{
  std::cout << "<Opt Declaration List> -> ";

  if(singletoken.first == "int"||
     singletoken.first == "bool" || 
     singletoken.first == "real")
     {
      std::cout << "<Declaration List>" << '\n';
      declaration_list();
     }
  else
  {
    std::cout << "<Empty>\n";
  }
}

void declaration_list()
{
  std::cout << "<Declaration List> -> <Declaration> ; <Declaration List 2>\n";
  declaration();
  if(singletoken.first == ";")
  {
    scanner();
    declaration_list2();
  }
  else
  {
    std::cout << "Expected a ;\n";
  }
}

void declaration_list2()
{
  std::cout << "<Declaration List 2> -> ";
  if(/*singletoken.second == "IDENTIFIER"||*/
     singletoken.first == "int" || 
     singletoken.first == "bool" ||
     singletoken.first == "real")
  {
    std::cout << "<Declaration List>\n";
    //scanner();
    declaration_list();
  }
  else
  {
    std::cout << "<EMPTY>\n";
  }
}

void declaration()
{
  std::cout << "<Declaration> -> <Qualifier > <IDs>\n";
  qualifier();
  ids();
}

void ids()
{
  std::cout << "<IDs> -> <Identifier> <IDs 2>\n";
  // std::cout << "bruh\n";
    identifier();
    ids2();
}

void ids2()
{
  std::cout << "<IDs 2> -> ";
  if(singletoken.first == ",")
  {
    //std::cout << "Entered becasue: " << singletoken.first << '\n';
    //std::cout << "\n\nbruh PT2\n\n";
    std::cout << ", <IDs>\n";
    scanner();
    ids();
    
  }
  else
  {
    std::cout << "<Empty>\n";
  }
}

void statement_list()
{
  std::cout << "<Statement List> -> <Statement> <Statement List2>\n";
  statement();
  statement_list2();
}

void statement_list2()
{
  std::cout << "<Statement List 2> -> ";
  if (singletoken.first == "{" ||
      singletoken.first == "if" ||
      singletoken.first == "return" ||
      singletoken.first == "put" ||
      singletoken.first == "get" ||
      singletoken.first == "while" ||
      singletoken.second == "IDENTIFIER"
      )
  {
      std::cout << "<Statement List>\n";
      statement_list();
  }

  else
  {
    std::cout << "<Empty>\n";
  }
  
}

void statement()
{
  std::cout << "<Statement> -> ";

  if(singletoken.first == "return")
  {
    std::cout << "<Return>\n";
    return_rule();
  }
  else if(singletoken.first == "if")
  {
    std::cout << "<If>\n";
    if_rule();
  }
  else if(singletoken.first == "put")
  {
    std::cout << "<Print>\n";
    print_rule();
  }
  else if(singletoken.first == "get")
  {
    std::cout << "<Scan>\n";
    scan_rule();
  }
  else if(singletoken.first == "while")
  {
    std::cout << "<While>\n";
    while_rule();
  }
  else if(singletoken.second == "IDENTIFIER")
  {
    std::cout << "<Identifier>\n";
    assign();
  }
  else if(singletoken.first == "{")
  {
    std::cout << "<Compound>\n";
    compound();
  }
  else
  {
    errorresult(singletoken.first, "statement");
  }
}

void compound()
{
  std::cout << "<Compound> -> { <Statement List> }\n";
  if (singletoken.first == "{")
  {
    scanner();
    statement_list();
  }
  else 
  {
    errorresult(singletoken.first, "{");
  }
  if (singletoken.first == "}")
  {
    scanner();
  }
  else
  {
    errorresult(singletoken.first, "}");
  }
}

void assign()
{
  std::cout << "<Assign> -> <Identifier> = <Expression>;\n";
  if(singletoken.second == "IDENTIFIER")
  {
    // std::cout << "\n\nBRUH 3\n\n";
    identifier();
  }
  if(singletoken.first == "=")
  {
    scanner();
  }
  else
  {
    errorresult(singletoken.first, "=");
  }
  expression();
  if(singletoken.first == ";")
  {
    scanner();
  }
  else
  {
    errorresult(singletoken.first, ";");
  }
}

void if_rule()
{
  std::cout << "<If> -> if ( <Condition> ) <Statement> <if 2>\n";
  if(singletoken.first == "if")
  {
    scanner();
  }
  else
  {
    errorresult(singletoken.first, "if");
  }
  if(singletoken.first == "(")
  {
    scanner();
    condition();
  }
  else
  {
    errorresult(singletoken.first, "(");

  }
  if(singletoken.first == ")")
  {
    scanner();
  }
  else 
  {
    errorresult(singletoken.first, ")");

  }
  statement();
  if_rule2();
}

void if_rule2()
{
  std::cout << "<If 2> ::= fi |  else <Statement> fi\n";
  if(singletoken.first == "else")
  {
    statement();
    if(singletoken.first == "fi")
    {
      scanner();
    }
    else
    {
     errorresult(singletoken.first, "fi");

    }
  }
  else if(singletoken.first == "fi")
  {
    scanner();
  }
  else
  {
    errorresult(singletoken.first, "else or fi");
  }
}

void return_rule()
{
  std::cout << "<Return> -> return <Return 2>\n";

  if(singletoken.first == "return")
  {
    scanner();
  }
  else
  {
    errorresult(singletoken.first, "return");
  }
  return_rule2();
}

void return_rule2()
{
  std::cout << "<Return 2> -> ";
  if(nexttk(0).first != ";")
  {
    std::cout << "return <Expression>;\n";
    expression();
    if(singletoken.first == ";")
    {
      scanner();
    }
    else
    {
      
      std::cout << "Expected a ;\n";
    }
  }
  else if (singletoken.first == ";")
  {
    std::cout << ";";
    scanner();
  }
  else
  {
    errorresult(singletoken.first, "; or an expression");
  }
}

void print_rule()
{
  std::cout << "<Print> -> put ( <Expression>);\n";
  if(singletoken.first == "put")
  {
    scanner();
  }
  else
  {
    errorresult(singletoken.first, "put");
  }
  if(singletoken.first == "(")
  {
    scanner();
    expression();
    if(singletoken.first == ")")
    {
      scanner();
    }
    else
    {
      errorresult(singletoken.first, ")");
    }
  }
  else
  {
    errorresult(singletoken.first, ")");
  }
  if(singletoken.first == ";")
  {
    scanner();
  }
  else
  {
    errorresult(singletoken.first, ";");
  }
    
}

void scan_rule()
{
  std::cout << " <Scan> -> get ( <IDs> );\n";
  if(singletoken.first == "get")
  {
    scanner();
  }
  else 
  {
    errorresult(singletoken.first, "get");

  }
  if(singletoken.first == "(")
  {
    scanner();
    ids();
  }
  else
  {
    errorresult(singletoken.first, "(");

  }
  if(singletoken.first == ")")
  {
    scanner();
  }
  else
  {
    errorresult(singletoken.first, ")");
  }
  if(singletoken.first == ";")
  {
    scanner();
  }
  else
  {
    errorresult(singletoken.first, ";");
  }
}

void while_rule()
{
  std::cout << "<While> ::= while ( <Condition> ) <Statement> endwhile\n";
  if(singletoken.first == "while")
  {
    scanner();
  }
  else
  {
    errorresult(singletoken.first, "while");

  }

  if(singletoken.first == "(")
  {
    scanner();
    condition();
    if(singletoken.first == ")")
    {
      scanner();
    }
    else
    {
    errorresult(singletoken.first, ")");
    }
  }
  else
  {
    errorresult(singletoken.first, "(");
  }
  statement();
  if(singletoken.first == "endwhile")
  {
    scanner();
  }
  else
  {
    errorresult(singletoken.first, "endwhile");
  }
}

void condition()
{
  std::cout << "<Condition> ::= <Expression> <Relop> <Expression>\n";
  expression();
  relop();
  expression();
}

void relop()
{
  std::cout << "<Relop> -> ";
  if(singletoken.first == "==")
  {
    std::cout << "==\n";
    scanner();
  }
  else if (singletoken.first == "!=")
  {
    std::cout << "!=\n";
    scanner();
  }
  else if (singletoken.first == ">")
  {
    std::cout << ">\n";
    scanner();
  }
  else if (singletoken.first == "<")
  {
    std::cout << "<\n";
    scanner();
  }
  else if (singletoken.first == "<=")
  {
    std::cout << "<=\n";
    scanner();
  }
  else if (singletoken.first == "=>")
  {
    std::cout << "=>\n";
    scanner();
  }
  else
  {
    errorresult(singletoken.first, "== | != | > | < | <= | =>");
  }
}

void expression()
{
  std::cout << "<Expression> -> <Term> <Expression Prime>\n";
  term();
  expression_prime();
}

void expression_prime()
{
  std::cout << "<Expression Prime> -> ";

  if (singletoken.first == "+")
  {
    std::cout << "+ <Term> <Expression Prime>\n";
    scanner();
    term();
    expression_prime();
  }
  else if(singletoken.first == "-")
  {
    std::cout << "- <Term> <Expression Prime>\n";
    scanner();
    term();
    expression_prime();
  }
  else
  {
    std::cout << "<Empty>\n";
    //std::cout << "\n\nSCANNING\n\n";
  }
}

void term()
{
  std::cout << "<Term> -> <Factor> <Term Prime>\n";
  factor();
  term_prime();
}


void term_prime()
{ 
  std::cout << "<Term Prime> -> ";
  if (singletoken.first == "*")
  {
    std::cout << "*<Factor> <Term Prime>\n";
    scanner();
    factor();
    term_prime();
  }
  else if(singletoken.first == "/")
  {
    std::cout << "/ <Factor> <Term Prime>\n";
    scanner();
    factor();
    term_prime();
  }
  else
  {
    std::cout << "<Empty>\n";
  }
}

void factor()
{
  std::cout << "<Factor> -> ";
  
  if(singletoken.first == "-")
  {
    std::cout << " - <Primary>\n";
    scanner();
    primary();
  }
  else if (singletoken.second == "IDENTIFIER" ||
           singletoken.second == "INTEGER" || 
           singletoken.first == "(" ||
           singletoken.first == "true" ||
           singletoken.first == "false" ||
           singletoken.second == "REAL")
  {
    std::cout << "<Primary>\n";
    primary();
  }
  else
  {
    errorresult(singletoken.first, "primary");
  }
}

void primary()
{
  std::cout << "<Primary> ->";
  if(singletoken.second == "IDENTIFIER")
  {
    std::cout << "<Identifier>\n";
    // std::cout << "\n\nBruh 4\n\n";
    identifier();
    primary2();
  }
  else if(singletoken.second == "INTEGER")
  {
    std::cout << "<Integer>\n";
    integer();
  }
  else if(singletoken.second == "REAL")
  {
    std::cout << "<Real>\n";
    real();
  }
  else if(singletoken.first == "(")
  {
    std::cout << "(<Expression>)\n";
    scanner();
    expression();
    if(singletoken.first == ")")
    {
      scanner();
    }
    else
    {
      // std::cout << "\n\nBRUHHHHH\n\n";
     errorresult(singletoken.first, ")");
    }
  }

  else if(singletoken.first == "true")
  {
    std::cout << "true\n";
    scanner();
  }
  else if(singletoken.first == "false")
  {
    std::cout << "false";
    scanner();
  }
  else
  {
    std::cout << "Expected a Integer, real, (, ), true, or false\n";
  }
}

void primary2()
{
  std::cout << "<Primary 2> -> ";

  if(singletoken.first == "(")
  {
    std::cout << "(<IDs>)\n";
    scanner();
    ids();
    if(singletoken.first == ")")
    {
      scanner();
    }
    else
    {
      // std::cout<< "HERE!!!\n";
    errorresult(singletoken.first, ")");

    }
  }
  else
  {
    std::cout << "<EMPTY>\n";
  }
}

void identifier()
{
  if(singletoken.second == "IDENTIFIER")
  {
    std::cout << "<Identifier> -> " << singletoken.first << '\n';
    scanner();
  }
  else
  {
    errorresult(singletoken.first, "IDENTIFIER");
  }
}

void integer()
{
  if(singletoken.second == "INTEGER")
  {
    std::cout << "<Integer> -> " << singletoken.first << '\n';
    scanner();
  }
  else
  {
    errorresult(singletoken.first, "INTEGER");

  }
}

void real()
{
  if(singletoken.second == "REAL")
  {
    std::cout << "<Real> -> " << singletoken.first << '\n';
    scanner();
  }
  else
  {
    errorresult(singletoken.first, "REAL");
  }
}

//function to return the error result with the line number, file, and type of error
void errorresult(std::string tokenresult, std::string type)
{
  std::cout << "=================================================\n";  
  std::cout << "Expected a " << type << " for token: " << tokenresult << ", In line number, " << tokensinfoglobal[infoi].first << ", In file: " << tokensinfoglobal[infoi].second << '\n';
  std::cout << "=================================================\n";
  exit(1);
}