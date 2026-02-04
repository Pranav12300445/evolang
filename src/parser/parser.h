#pragma once
#include <vector>
#include <memory>
#include "lexer/lexer.h"
#include "ast/ast.h"

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);

    std::unique_ptr<Program> parse();

private:
    const std::vector<Token>& tokens;
    size_t pos = 0;

    const Token& peek() const;
    const Token& advance();
    bool match(TokenType type);

    std::unique_ptr<Stmt> parseStatement();
    std::unique_ptr<Stmt> parsePrintStatement();
};
