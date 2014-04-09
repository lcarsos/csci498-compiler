%{
  #include "ast.h"
  #include <iostream>
  #include <string>

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

%token <integer>    integer
%token <real>       real
%token <str>        identifier
%token <str>        unaryOperatorKeyword
%token <str>        operatorKeyword

// Reserved words.
%token <str>        constQualifier
%token <str>        elseKeyword
%token <str>        ifKeyword
%token <str>        returnKeyword
%token <str>        whileKeyword

%type <node>        Assignment
%type <node>        Block
%type <node>        Declaration
%type <node>        Declarations
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

%code requires {
  #include "ast.h"
  using namespace std;

  // Structs, unlike unions, allow class members.
  struct YYSTYPE {
    int integer;
    double real;
    string str;
    ASTNode node;

    // We should probably have a reasonable default constructor.
    YYSTYPE()
    : integer(), real() {}
  };
}

%%
// TODO: Fix the 2 shift/reduce.

Program:
  Statements {
    $$ = $1;
    $$.type = ASTNode::Program;
    $$.print_tree(cout);
  }
;

Statements:
  Statements Statement {
    $$.addChild($2);
  }
| Statement {
    $$ = ASTNode(ASTNode::Block);
    $$.addChild($1);
  }
;

Statement:
  Declarations ';' {
    $$ = $1;
  }
| Assignment ';' {
    $$ = $1;
  }
| Expression ';' {
    $$ = $1;
  }
| Block {
    $$ = $1;
  }
| IfStatement {
    $$ = $1;
  }
| WhileStatement {
    $$ = $1;
  }
| ReturnStatement {
    $$ = $1;
  }
| ';' {
    $$ = ASTNode(ASTNode::Expression);
  }
;

Declarations:
  Type DeclList {
    $$ = ASTNode(ASTNode::Declarations);
	$$.addChild($1);
	$$.addChild($2);
  }
;

DeclList:
  Declaration {
    $$ = $1;
  }
| DeclList ',' Declaration {
    $$.addChild($3);
  }
;

Declaration:
  Assignment {
    $$ = ASTNode(ASTNode::Declaration);
    $$.addChild($1);
  }
| identifier {
    $$ = ASTNode(ASTNode::Declaration);
    $$.addChild(ASTNode(ASTNode::Symbol, $1));
  }
;

Type:
  constQualifier Type {
    $$ = $2;
    $$.makeConst();
  }
| identifier {
    $$ = ASTNode(ASTNode::Symbol, $1);
  }
;

Assignment:
  identifier '=' Expression {
    $$ = ASTNode(ASTNode::Assignment);
    $$.addChild(ASTNode(ASTNode::Symbol, $1));
    $$.addChild($3);
  }
;

Block:
  '{' Statements '}' {
    $$ = $2;
  }
  | '{' '}' {
    $$ = ASTNode(ASTNode::Block);
  }
;

Expression:
  '(' Expression ')' {
    $$ = $2;
  }
| Expression operatorKeyword Value {
    $$ = ASTNode(ASTNode::Expression, $2);
    $$.addChild($1);
    $$.addChild($3);
  }
| Value {
    $$ = $1;
  }
;

Value:
  identifier {
    $$ = ASTNode(ASTNode::Symbol, $1);
  }
| Literal {
    $$ = $1;
  }
;

Literal:
// TODO: const char* and char literals. (Eventually)
  integer {
    $$ = ASTNode(ASTNode::Symbol, to_string($1));
  }
| real {
    $$ = ASTNode(ASTNode::Symbol, to_string($1));
  }
;

IfStatement:
  ifKeyword '(' Expression ')' Block {
    $$ = ASTNode(ASTNode::If);
    $$.addChild($3);
    $$.addChild($5);
  }
| ifKeyword '(' Expression ')' Block ElseStatement  {
    $$ = ASTNode(ASTNode::If);
    $$.addChild($3);
    $$.addChild($5);
    $$.addChild($6);
  }
;

ElseStatement:
  elseKeyword Block {
    $$ = $2;
  }
| elseKeyword IfStatement {
    $$ = $2;
  }
;

WhileStatement:
  whileKeyword '(' Expression ')' Block {
    $$ = ASTNode(ASTNode::While);
    $$.addChild($3);
    $$.addChild($5);
  }
;

ReturnStatement:
  returnKeyword Expression ';' {
    $$ = ASTNode(ASTNode::Return);
    $$.addChild($2);
  }
;

%%

void yyerror(const char* msg) {
	cerr << "[Error] " << msg << endl;
  }
