#include <iostream>
#include <vector>
#include <stack>
#include "parser.h"

std::vector<std::pair<std::string, std::string>> tokensglobal;
std::pair<std::string, std::string> singletoken;
std::vector<std::pair<std::string, std::string>>::iterator it;

void scanner()
{
  std::cout << "||   Token: " << (*it).second << "      Lexeme: " << (*it).first << " || \n";
  singletoken = *(++it);
}

std::pair<std::string, std::string> nexttk(int step) 
{
  auto next_token = *(it + step);
  return next_token;
}


void parser(const std::vector<std::pair<std::string, std::string>> &tokens)
{
  tokensglobal = tokens;
  for(auto i : tokensglobal )
  {
    std::cout << i.first << "\n i.second\n";
  }
  it = tokensglobal.begin();
  singletoken = *it;
  std::cout << "HERE" << (*it).first << (*it).second;
  check();
  rat23s();
}

void check()
{
    std::cout << "CHECK\n" << (*it).first << (*it).second << "\n\n";
}

void rat23s()
{
  // if (switch) 
  std::cout << "<Rat23S> ::= <Opt Function Definitions> # <Opt Declaration List> # <Statement List>\n";
  opt_functions();
  if (singletoken.first == "#") 
    scanner();
  else 
  {
    std::cout << "Expected #\n"; 
    exit(1);
  }

  opt_declaration_list();

  if (singletoken.first == "#") 
    scanner();
  else
  {
    std::cout << "Expected #\n";
    exit(1);
  }

  statement_list();
}

void opt_functions()
{
  std::cout << "<Opt Function Definitions> ::= <Function Definitions> | <Empty>\n";
  function_def();
}

void function_def()
{
  std::cout << "<Function Definitions> ::= <Function> <FunctionDefintion2>>\n";
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
  std::cout << "<Function> ::= function <Identifier> ( <Opt Parameter List> ) <Opt Declaration List> <Body>\n";
  if(singletoken.first == "function")
  {
    scanner();
  }
  else
  {
    std::cout << "TOKEN: " << singletoken.first << '\n';
    std::cout << "Expected a function keyword\n";
    exit(1);
  }
  std::cout << "\n\nBruh 5\n\n";
  identifier();
  if(singletoken.first == "(")
  {
    scanner();
  }
  else
  {
    std::cout << "Expected a (";
    exit(1);
  }
  opt_parameter_list();
  if(singletoken.first == ")")
    scanner();
  else
  {
    std::cout << "Expected a )";
    exit(1);
  }
  opt_declaration_list();
  body();
}

void opt_parameter_list()
{
  std::cout << "  <Opt Parameter List> -> ";
  if(!(nexttk(0).first == ")"))
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
  std::cout << "<Parameter> ::= <IDs > <Qualifier>\n";
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
    std::cout << "Expected a INT, REAL, or BOOL\n";
    exit(1);
  }
}

void body()
{
  std::cout << " <Body> -> {<Statement List>}";
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
      exit(1);
    }
  }
  else
  {
    std::cout << "expected a {\n";
    exit(1);
  }
}

void opt_declaration_list()
{
  std::cout << "<Opt Declaration List> ->";

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
  std::cout << "<Declaration List 2> -> \n";
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
  if(singletoken.second == "IDENTIFIER")
  {
    identifier();
    ids2();
  }
  else
  {
    ids2();
  }
}

void ids2()
{
  std::cout << "<IDs 2> -> ";
  if(singletoken.first == ",")
  {
    std::cout << "Entered becasue: " << singletoken.first << '\n';
    //std::cout << "\n\nbruh PT2\n\n";
    std::cout << ", <IDs>\n";
    scanner();
    ids();
    std::cout << "\n\nbruh 2\n\n";
    identifier();
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
  else if(singletoken.first == "print")
  {
    std::cout << "<Print>\n";
    print_rule();
  }
  else if(singletoken.first == "scan")
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
  else if(singletoken.second == "{")
  {
    compound();
  }
  else
  {
    std::cout << "expected a statement\n";
  }
}

void compound()
{
  std::cout << "<Compound> ::= { <Statement List> }\n";
  if (singletoken.first == "{")
  {
    scanner();
    statement_list();
  }
  else 
  {
    std::cout << "Expected a {\n";
    exit(1);
  }
  if (singletoken.first == "}")
  {
    scanner();
  }
}

void assign()
{
  std::cout << "<Assign> -> <Identifier> = <Expression>;\n";
  if(singletoken.second == "IDENTIFIER")
  {
    std::cout << "\n\nBRUH 3\n\n";
    identifier();
  }
  if(singletoken.first == "=")
  {
    scanner();
  }
  expression();
  if(singletoken.first == ";")
  {
    scanner();
  }
  else
  {
    std::cout << "Expected a ;\n";
    exit(1);
  }
}

void if_rule()
{
  std::cout << "<If> ::= if ( <Condition> ) <Statement> <if 2>\n";
  if(singletoken.first == "if")
  {
    scanner();
  }
  else
  {
    std::cout << "Expected a if\n";
    exit(1);
  }
  if(singletoken.first == "(")
  {
    scanner();
    condition();
  }
  else
  {
    std::cout << "Expected a (\n";
    exit(1);
  }
  if(singletoken.first == ")")
  {
    scanner();
  }
  else 
  {
    std::cout << "Expected a )\n";
    exit(1);
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
      std::cout << "Exptected fi\n";
      exit(1);
    }
  }
  else if(singletoken.first == "fi")
  {
    scanner();
  }
  else
  {
    std::cout << "Expected a else or fi\n";
    exit(1);
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
    std::cout << "Expected a return\n";
    exit(1);
  }
  return_rule2();
}

void return_rule2()
{
  std::cout << "<Return 2> -> ";
  if(nexttk(0).second != ";")
  {
    std::cout << "return <Expression>;\n";
    expression();
  }
  else if (singletoken.first == ";")
  {
    std::cout << ";";
    scanner();
  }
  else
  {
    std::cout << "Expected a ; or an expression\n";
    exit(1);
  }
}

void print_rule()
{
  std::cout << "<Print> ::= put ( <Expression>);\n";
  if(singletoken.first == "put")
  {
    scanner();
  }
  else
  {
    std::cout << "Expected a put";
    exit(1);
  }
  if(singletoken.first == "(")
  {
    scanner();
    expression();
  }
  else
  {
    std::cout << "Expected a (\n";
    exit(1);
  }
  if(singletoken.first == ";")
  {
    scanner();
  }
  else
  {
    std::cout << "expected a ;\n";
    exit(1);
  }
    
}

void scan_rule()
{
  std::cout << " <Scan> ::= get ( <IDs> );\n";
  if(singletoken.first == "get")
  {
    scanner();
  }
  else 
  {
    std::cout << "Expected a get\n";
    exit(1);
  }
  if(singletoken.first == "(")
  {
    scanner();
    ids();
  }
  else
  {
    std::cout << "Exptected a (\n";
    exit(1);
  }
  if(singletoken.first == ")")
  {
    scanner();
  }
  else
  {
    std::cout << "Expected a )\n";
  }
  if(singletoken.first == ";")
  {
    scanner();
  }
  else
  {
    std::cout << "Expected a ;\n";
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
    std::cout << "Expected a while\n";
    exit(1);
  }

  if(singletoken.first == "(")
  {
    scanner();
    condition();
  }
  else
  {
    std::cout << "Expected a (\n";
    exit(1);
  }
  if(singletoken.first == ")")
  {
    scanner();
  }
  else
  {
    std::cout << "Expected a )\n";
    exit(1);
  }
  statement();
  if(singletoken.first == "endwhile")
  {
    scanner();
  }
  else
  {
    std::cout << "Expected a endwhile\n";
    exit(1);
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
  std::cout << "<Relop> ::= == | != | > | < | <= | =>\n";
  if(singletoken.first == "==")
  {
    scanner();
  }
  else if (singletoken.first == "!=")
  {
    scanner();
  }
  else if (singletoken.first == ">")
  {
    scanner();
  }
  else if (singletoken.first == "<")
  {
    scanner();
  }
  else if (singletoken.first == "<=")
  {
    scanner();
  }
  else if (singletoken.first == "=>")
  {
    scanner();
  }
  else
  {
    std::cout << "Expected == | != | > | < | <= | =>\n";
    exit(1);
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
    scanner();
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
    std::cout << "Expected a Primary\n";
    exit(1);
  }
}

void primary()
{
  std::cout << "<Primary> ->";
  if(singletoken.second == "IDENTIFIER")
  {
    std::cout << "<Identifier>\n";
    std::cout << "\n\nBruh 4\n\n";
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
  }
  else if(singletoken.first == ")")
  {
    scanner();
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
  std::cout << "Primary 2 ->";

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
      std::cout<< "HERE!!!\n";
      std::cout << "Expected a )\n";
      exit(1);
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
    std::cout << " <Identifier> -> " << singletoken.first << '\n';
    scanner();
  }
  else
  {
    std::cout << "Expected an IDENTIFIER\n" << "for: " << singletoken.first;
    exit(1);
  }
}

void integer()
{
  if(singletoken.second == "INTEGER")
  {
    std::cout << " <Integer> -> " << singletoken.first << '\n';
    scanner();
  }
  else
  {
    std::cout << "Expected an Integer\n";
    exit(1);
  }
}

void real()
{
  if(singletoken.second == "REAL")
  {
    std::cout << " <Real> -> " << singletoken.first << '\n';
    scanner();
  }
  else
  {
    std::cout << "Expected a Real\n";
    exit(1);
  }
}