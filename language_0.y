%{
	#include "language_0_parser.hpp"

	#include <iostream>

	// From flex
	int yylex();

	void yyerror(const char*);
%}

// Debugging flags.
// Some of them need yydebug assigned to 1 before calling yyparse().
%debug
%error-verbose
%define parse.lac full

// This adds additonal arguments to yyparse. We can use it to return
//    the AST, but until then it just gets in the way.
//%parse-param {ASTNode& program}.

// Tokens are declared like so, where A is the member of the union
//   to store the value of B in, when found. B is just a name.
// %token <A> B.
// TODO: More tokens. See lang_design.txt.
%token <integer> Integer
%token <real> Float
%token <identifier> Identifier

// This defines the type of everything we use in our grammar.
// TODO: Design our AST so these can have meaningful types.
%type <aMember> Assignment
%type <aMember> Block
%type <aMember> Declaration
%type <aMember> Declarations
%type <aMember> DeclRepeat
%type <aMember> DeclRepeats
%type <aMember> ElseStatement
%type <aMember> Expression
%type <aMember> IfStatement
%type <aMember> IntOperator
%type <aMember> Operator
%type <aMember> Program
%type <aMember> ReturnStatement
%type <aMember> Statement
%type <aMember> Statements
%type <aMember> Type
%type <aMember> Value
%type <aMember> WhileStatement

%union {
	int integer;
	double real;
	char* identifier;
	void* aMember; // Place holder so that it builds.
}

%%

Program:
  Statements
;

Block:
  '{' Statements '}'
| Statement

Statements:
  Statements Statement
| Block
| Block Statements
;

Statement:
  Declarations ';'
| Expression ';'
| IfStatement
| WhileStatement
| ReturnStatement ';'
| ';'
;

// Some of this declaration code could be cleaned up.
Declarations:
  Declaration
| Type DeclRepeat
;

DeclRepeats:
  DeclRepeat
| DeclRepeat ',' DeclRepeat
;

DeclRepeat:
  Assignment
| Identifier

Declaration:
  Type Assignment
| Type Identifier
;

Expression:
  Assignment
| '(' Expression ')'
| Value Operator Expression
| Value
;

IfStatement:
// TODO: Make an IfKeyword token.
  'if' '(' Expression ')' Block
| 'if' '(' Expression ')' Block ElseStatement
;

ElseStatement:
// TODO: Make an ElseKeyword token.
  'else' Block
| 'else' IfStatement

WhileStatement:
// TODO: Make a WhileKeyword token.
  'while' '(' Expression ')' Block

ReturnStatement:
// TODO: Make a ReturnKeyword token.
  'return' Expression

// For now lump all operators in one. Let a future step in the parser do
//   operator precedence/type checking for now.
// We might need the scanner to handle multi-character literals here.
// TODO: Make an Operator token or a token for each operator.
Operator:
  '~'
| '!'
| '%'
| '^'
| '&'
| '&&'
| '*'
| '-'
| '+'
| '|'
| '||'
| '>>'
| '>>'
| '/'
;

// An optional operator for things that only take ints as there params.
// Not currently used.
// TODO: Make an IntOperator token or a token for each operator.
IntOperator:
  '>>'
| '<<'
;

Assignment:
  Identifier '=' Expression

Value:
  Identifier
| Integer
| Float
;

Type:
// TODO: Make a ConstKeyword token.
  'const' Type
| Identifier
// TODO: Make an IntType token.
| 'int'
;

%%

void yyerror(const char* msg) {
	std::cerr << "[Error] " << msg << std::endl;
}
