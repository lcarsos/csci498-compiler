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
    std::ofstream error(output_file+".err");

    int result = yyparse(program, error);
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
