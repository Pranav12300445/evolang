#include "interpreter/interpreter.h"
#include <iostream>
#include <stdexcept>

void Interpreter::interpret(const Program& program) {
    for (const auto& stmt : program.statements) {
        execute(stmt.get());
    }
}

void Interpreter::execute(const Stmt* stmt) {
    if (auto p = dynamic_cast<const PrintStmt*>(stmt))
        executePrint(p);
    else if (auto l = dynamic_cast<const LetStmt*>(stmt))
        executeLet(l);
}

void Interpreter::executeLet(const LetStmt* stmt) {
    environment[stmt->name] = evaluate(stmt->initializer.get());
}

void Interpreter::executePrint(const PrintStmt* stmt) {
    std::cout << evaluate(stmt->expression.get()) << std::endl;
}

std::string Interpreter::evaluate(const Expr* expr) {
    if (auto s = dynamic_cast<const StringExpr*>(expr))
        return s->value;

    if (auto v = dynamic_cast<const VariableExpr*>(expr)) {
        if (!environment.count(v->name))
            throw std::runtime_error("Undefined variable: " + v->name);
        return environment[v->name];
    }

    throw std::runtime_error("Unknown expression");
}
