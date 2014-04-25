#include "language_0_parser.hpp"

#include <iostream>
#include <fstream>

// Not declared in the header.
int yyparse();

int main(int argc, char *argv[]) {
// Enable this when you need token-by-token debugging.
//    yydebug = 1;
    if (argc != 2) {
        cerr << "Requires output token in command line";
        return 3;
    }

    string output_file = string(argv[1]);

    ASTNode program;
    std::ofstream output_err(output_file+".err");
    std::ofstream output_a(output_file+".a");
    std::ofstream output_p(output_file+".p");
    std::ofstream output_ir(output_file+".ir");

    // Parse!
    int result = yyparse(program, output_err);

    // Print parse tree
    program.print_tree(output_p);

    // Print abstract syntax tree
    program.print_tree(output_a);



    // Generate IR code
    /* PUT STUFF HERE */



    // Close files
    output_err.close();
    output_a.close();
    output_p.close();
    output_ir.close();

    switch (result) {
        case 0:
            // Silence is golden.
            break;
        case 1:
            // Bison prints syntax errors, so we won't.
            break;
        // If either of these happen, bad things have happened.
        case 2:
            std::cout << "Memory error!" << std::endl;
            break;
        default:
            std::cout << "Unknown error." << std::endl;
    }

    return result;
}
