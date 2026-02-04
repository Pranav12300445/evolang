#pragma once
#include "ast/ast.h"

class Interpreter {
public:
    void interpret(const Program& program);

private:
    void execute(const Stmt* stmt);
    void executePrint(const PrintStmt* stmt);
};
