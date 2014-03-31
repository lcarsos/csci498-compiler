%{
	#include <iostream>

	// From flex
	int yylex();

	void yyerror(const char*);
%}

// Debugging flags.
// Some of them need yydebug assigned to 1 before calling yyparse().
//   (They are VERY verbose!)
%debug
%error-verbose
%define parse.lac full

// This adds additonal arguments to yyparse. We can use it to return
//    the AST, but until then it just gets in the way.
//%parse-param {ASTNode& program}.

%token <node>       binaryOp
%token <identifier> identifier
%token <integer>    integer
%token <real>       real
%token <node>       unaryOp

%type <node>        Assignment
%type <node>        Block
%type <node>        Declaration
%type <node>        Declarations
%type <node>        DeclBase
%type <node>        DeclList
%type <node>        ElseStatement
%type <node>        Expression
%type <node>        IfStatement
%type <node>        Literal
%type <node>        Program
%type <node>        ReturnStatement
%type <node>        Statement
%type <node>        Statements
%type <node>        Type
%type <node>        Value
%type <node>        WhileStatement

%union {
	int integer;
	double real;
	char identifier[1000];
	int op; // TODO: Make this an enum class for operators.
	void* node;
}

%%
// TODO: Fix the 3 shift/reduce and 2 reduce/reduce conflicts.

Program:
  Statements
;

Statements:
  Statements Statement
| Statement
;

Statement:
  Declarations ";"
| Expression ";"
| Block
| IfStatement
| WhileStatement
| ReturnStatement ";"
| ";"
;

Block:
  "{" Statements "}"
;

// Declarations code could still use some work.
Declarations:
  Declaration
| DeclList
;

DeclList:
  DeclBase
| DeclList "," DeclBase
;

DeclBase:
  Assignment
| identifier
;

Assignment:
// TODO: Handle Expressions with pointers. (Eventually)
  identifier "=" Expression
;

Type:
  "const" Type
| identifier
// For now, we'll just hard code the built-in type(s).
| "int"
;

Declaration:
  Type DeclBase
;

Expression:
  Assignment
| "(" Expression ")"
| Expression binaryOp Expression
| unaryOp Expression
| Value
;

Value:
  identifier
| Literal
;

Literal:
// TODO: const char* and char literals. (Eventually)
  integer
| real
;

IfStatement:
  "if" "(" Expression ")" Block
| "if" "(" Expression ")" Block ElseStatement
;

ElseStatement:
  "else" Block
| "else" IfStatement
;

WhileStatement:
  "while" "(" Expression ")" Block
;

ReturnStatement:
  "return" Expression ";"
;

%%

void yyerror(const char* msg) {
	std::cerr << "[Error] " << msg << std::endl;
}
