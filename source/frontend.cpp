#include "language_0_parser.hpp"

#include "ast.h"

#include <iostream>
#include <fstream>

// Not declared in the header.
int yyparse(ASTNode& program, std::ostream& error);

int main(int argc, char** argv) {
// Enable this when you need token-by-token debugging.
//    yydebug = 1;
    std::vector<std::string> args(&argv[0], &argv[argc]);

    if (args.size() != 2) {
        std::cerr << "Usage: " << args[0] << " OUTPUT" << std::endl;
        std::cerr << "Generate OUTPUT.{err,a,p,ir} from stdin." << std::endl;
        return 3;
    }

    std::string filename = args[1];

    std::ofstream error     (filename + ".err");
    std::ofstream ast       (filename + ".a");
    std::ofstream parsetree (filename + ".p");
    std::ofstream ir_code   (filename + ".ir");

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
