#include "parser/parser.h"
#include <stdexcept>

Parser::Parser(const std::vector<Token>& t) : tokens(t) {}

const Token& Parser::peek() const {
    return tokens[pos];
}

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
    if (match(TokenType::PRINT)) {
        return parsePrintStatement();
    }

    throw std::runtime_error("Unexpected token in statement");
}

std::unique_ptr<Stmt> Parser::parsePrintStatement() {
    if (!match(TokenType::STRING)) {
        throw std::runtime_error("Expected string after print");
    }

    auto expr = std::make_unique<StringExpr>(
        tokens[pos - 1].lexeme
    );

    return std::make_unique<PrintStmt>(std::move(expr));
}
