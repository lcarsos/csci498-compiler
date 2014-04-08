%option noyywrap
%{
	#include "language_0_parser.hpp"
%}

BitwiseOp     "|"|"&"|"^"|"~"|"<<"|">>"
ArithmeticOp  "+"|"-"|"*"|"/"|"%"|"++"|"--"
CompoundOp    "+="|"-="|"*="|"/="|"%="|"|="|"&="|"^="|"~="|"<<="|">>="
LogicOp       "||"|"&&"|"!"
ComparisionOp "<"|">"|"<="|">="|"!="|"=="

%%

[ \n\t\r]+ {
	// Eat whitespace.
	continue;
}

"if" {
	return ifKeyword;
}
"else" {
	return elseKeyword;
}
"while" {
	return whileKeyword;
}
"return" {
	return returnKeyword;
}
"const" {
	return constQualifier;
}


[0-9]+ {
	yylval.integer = atoi(yytext);
	return integer;
}

[0-9]+\.?[0-9]*([eE][+-]?[0-9]+)? {
	yylval.real = atof(yytext);
	return real;
}

[a-zA-Z_]+[a-zA-Z_0-9]* {
	yylval.str = yytext;
	return identifier;
}

{BitwiseOp}|{ArithmeticOp}|{CompoundOp}|{LogicOp}|{ComparisionOp} {
	yylval.str = yytext;
	return operatorKeyword;
}

. {
	// Pass unknown characters through to Bison, they might be important.
	return yytext[0];
}

%%
