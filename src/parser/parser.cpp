#include "parser/parser.h"
#include <stdexcept>

Parser::Parser(const std::vector<Token>& t) : tokens(t) {}

const Token& Parser::peek() const { return tokens[pos]; }

const Token& Parser::advance() {
    if (pos < tokens.size()) pos++;
    return tokens[pos - 1];
}

bool Parser::match(TokenType type) {
    if (peek().type == type) {
        advance();
        return true;
    }
    return false;
}

std::unique_ptr<Program> Parser::parse() {
    auto program = std::make_unique<Program>();
    while (peek().type != TokenType::EOF_TOKEN) {
        program->statements.push_back(parseStatement());
    }
    return program;
}

std::unique_ptr<Stmt> Parser::parseStatement() {
    if (match(TokenType::PRINT)) return parsePrintStatement();
    if (match(TokenType::LET))   return parseLetStatement();
    throw std::runtime_error("Unexpected statement");
}

std::unique_ptr<Stmt> Parser::parsePrintStatement() {
    auto expr = parseExpression();
    return std::make_unique<PrintStmt>(std::move(expr));
}

std::unique_ptr<Stmt> Parser::parseLetStatement() {
    if (!match(TokenType::IDENTIFIER))
        throw std::runtime_error("Expected variable name");

    std::string name = tokens[pos - 1].lexeme;

    if (!match(TokenType::EQUAL))
        throw std::runtime_error("Expected '='");

    auto init = parseExpression();
    return std::make_unique<LetStmt>(name, std::move(init));
}

std::unique_ptr<Expr> Parser::parseExpression() {
    if (match(TokenType::STRING))
        return std::make_unique<StringExpr>(tokens[pos - 1].lexeme);

    if (match(TokenType::IDENTIFIER))
        return std::make_unique<VariableExpr>(tokens[pos - 1].lexeme);

    throw std::runtime_error("Invalid expression");
}
