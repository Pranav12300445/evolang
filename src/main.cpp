#include <iostream>
#include <fstream>
#include <sstream>

#include "lexer/lexer.h"
#include "parser/parser.h"
#include "interpreter/interpreter.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: evolang <file.ev>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Could not open file\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    Lexer lexer(buffer.str());
    auto tokens = lexer.tokenize();

    Parser parser(tokens);
    auto program = parser.parse();

    Interpreter interpreter;
    interpreter.interpret(*program);

    return 0;
}
