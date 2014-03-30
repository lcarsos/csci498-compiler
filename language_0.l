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

constStr {
  return constKeyword;
}

commaStr {
  return comma;
}

elseStr {
  return elseKeyword;
}

whileStr {
  return whileKeyword;
}
returnStr {
  return returnKeyword;
}
intStr {
  return intType;
}
equalsStr {
  return equalsop;
}
semicolonStr {
  return semicolon;
}
bitandStr {
  return bitandop;
}

bitorStr {
  return bitorop;
}

xorStr {
  return bitxor;
}

bitnotStr {
  return bitnot;
}

shlStr {
  return shl;
}

shrStr {
  return shr;
}

logorStr {
  return logor;
}

logandStr {
  return logand;
}

lognotStr {
  return lognot;
}

addStr {
  return add;
}
subStr {
  return sub;
}

divStr {
  return divop;
}

mulStr {
  return mul;
}

modStr {
  return mod;
}
ifStr {
  return ifKeyword;
}

lBracketStr {
  return lBracket;
}

rBracketStr {
  return rBracket;
}

lParenStr {
  return lParen;
}

rParenStr {
  return rParen;
}

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
