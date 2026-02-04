#include "interpreter/interpreter.h"
#include <iostream>

void Interpreter::interpret(const Program& program) {
    for (const auto& stmt : program.statements) {
        execute(stmt.get());
    }
}

void Interpreter::execute(const Stmt* stmt) {
    if (auto printStmt = dynamic_cast<const PrintStmt*>(stmt)) {
        executePrint(printStmt);
    }
}

void Interpreter::executePrint(const PrintStmt* stmt) {
    if (auto str = dynamic_cast<const StringExpr*>(stmt->expression.get())) {
        std::cout << str->value << std::endl;
    }
}
