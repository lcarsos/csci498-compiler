#include "language_0_parser.hpp"

#include "ast.h"

#include <iostream>
#include <fstream>

// Not declared in the header.
int yyparse(ASTNode& program, std::ostream& error);

int main(int argc, char *argv[]) {
// Enable this when you need token-by-token debugging.
//    yydebug = 1;
    std::vector<std::string> args(argv, argc);
    if (args.length() != 2) {
        cerr << "Requires output token in command line";
        return 3;
    }

    string filename = args[1];

    std::ofstream error     = filename + ".err";
    std::ofstream ast       = filename + ".a";
    std::ofstream parsetree = filename + ".p";
    std::ofstream ir_code   = filename + ".ir";

    // Parse!
    ASTNode program;
    int parse_result = yyparse(program, error);

    // Print parse tree
    program.print_tree(parsetree);

    // Print abstract syntax tree
    program.print_tree(ast);

    // Generate IR code
    program.print_ir(ir_code);

    if (parse_result != 0) {
        return parse_result;
    }

    return 0;
}
