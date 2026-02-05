#pragma once
#include <memory>
#include <string>
#include <vector>

struct ASTNode {
    virtual ~ASTNode() = default;
};

// ===== Expressions =====
struct Expr : ASTNode {};

struct StringExpr : Expr {
    std::string value;
    explicit StringExpr(const std::string& v) : value(v) {}
};

struct VariableExpr : Expr {
    std::string name;
    explicit VariableExpr(const std::string& n) : name(n) {}
};

// ===== Statements =====
struct Stmt : ASTNode {};

struct PrintStmt : Stmt {
    std::unique_ptr<Expr> expression;
    explicit PrintStmt(std::unique_ptr<Expr> expr)
        : expression(std::move(expr)) {}
};

struct LetStmt : Stmt {
    std::string name;
    std::unique_ptr<Expr> initializer;

    LetStmt(const std::string& n, std::unique_ptr<Expr> init)
        : name(n), initializer(std::move(init)) {}
};

// ===== Program =====
struct Program : ASTNode {
    std::vector<std::unique_ptr<Stmt>> statements;
};
