#pragma once
#include <unordered_map>
#include <string>
#include "ast/ast.h"

class Interpreter {
public:
    void interpret(const Program& program);

private:
    std::unordered_map<std::string, std::string> environment;

    void execute(const Stmt* stmt);
    void executePrint(const PrintStmt* stmt);
    void executeLet(const LetStmt* stmt);
    std::string evaluate(const Expr* expr);
};
