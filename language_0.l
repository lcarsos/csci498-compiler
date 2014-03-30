%{

#include "language_0_parser.hpp"

%}

/* Tokens used here are defined in the bison file.
   TODO: Tokens for binary and uninary operators? */
ifStr           "if"
lBracketStr      "{"
rBracketStr      "}"
lParenStr        "("
rParenStr        ")"
bitandStr             "&"
bitorStr	      "|"
xorStr	              "^"
bitnotStr	      "~"
shlStr	              "<<"
shrStr	              ">>"
logorStr	      "||"
logandStr	      "&&"
lognotStr	      "!"
addStr	              "+"
subStr	              "-"
divStr	              "/"
mulStr	              "*"
modStr	              "%"
semicolonStr          ";"
constStr	      "const"
commaStr	      ","
elseStr		      "else"
whileStr	      "while"
returnStr	      "return"
equalsStr	      "="
intStr		      "int"
%%

constStr { return constKeyword; }

commaStr { return comma; }

elseStr { return elseKeyword; }

whileStr { return whileKeyword; }

returnStr { return returnKeyword; }

intStr { return intType; }

equalsStr { return equalsOp; }

semicolonStr { return semicolon; }

bitandStr { return bitandOp; }

bitorStr {  return bitorOp; }

xorStr { return bitxorOp; }

bitnotStr { return bitnotOp; }

shlStr { return shlOp; }

shrStr { return shrOp; }

logorStr { return logorOp; }

logandStr { return logandOp; }

lognotStr { return lognotOp; }

addStr { return addOp; }

subStr { return subOp; }

divStr { return divOp; }

mulStr { return mulOp; }

modStr { return modOp; }

ifStr { return ifKeyword; }

lBracketStr { return lBracket; }

rBracketStr { return rBracket; }

lParenStr { return lParen; }

rParenStr { return rParen; }

[+-]?[0-9]+ {
	yylval.integer = atoi(yytext);
	return Integer;
}
[+-]?[0-9]+\.?[0-9]*([eE][+-]?[0-9]+)? {
	yylval.real = atof(yytext);
	return Float;
}
[a-zA-Z_]+[a-zA-Z_0-9]* {
	yylval.identifier = strdup(yytext);
	return Identifier;
}

. {
	// Do nothing with unknown characters.
	continue;
}

%%
