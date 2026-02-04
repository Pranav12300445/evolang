#pragma once
#include <memory>
#include <string>
#include <vector>

// ===== Base Nodes =====
struct ASTNode {
    virtual ~ASTNode() = default;
};

// ===== Expressions =====
struct Expr : ASTNode {};

struct StringExpr : Expr {
    std::string value;
    explicit StringExpr(const std::string& val) : value(val) {}
};

// ===== Statements =====
struct Stmt : ASTNode {};

struct PrintStmt : Stmt {
    std::unique_ptr<Expr> expression;
    explicit PrintStmt(std::unique_ptr<Expr> expr)
        : expression(std::move(expr)) {}
};

// ===== Program Root =====
struct Program : ASTNode {
    std::vector<std::unique_ptr<Stmt>> statements;
};
