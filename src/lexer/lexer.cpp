#include "lexer/lexer.h"
#include <cctype>

Lexer::Lexer(const std::string& src) : source(src) {}

char Lexer::peek() const {
    if (pos >= source.size()) return '\0';
    return source[pos];
}

char Lexer::advance() {
    if (pos >= source.size()) return '\0';
    return source[pos++];
}

void Lexer::skipWhitespace() {
    while (std::isspace(peek())) advance();
}

Token Lexer::readString() {
    advance(); // opening quote
    std::string value;

    while (peek() != '"' && peek() != '\0') {
        value += advance();
    }

    if (peek() == '"') advance();
    return {TokenType::STRING, value};
}

Token Lexer::readIdentifier() {
    std::string value;
    while (std::isalnum(peek())) {
        value += advance();
    }

    if (value == "print") return {TokenType::PRINT, value};
    if (value == "let")   return {TokenType::LET, value};

    return {TokenType::IDENTIFIER, value};
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (peek() != '\0') {
        skipWhitespace();
        char c = peek();

        if (c == '\0') break;

        if (c == '"') {
            tokens.push_back(readString());
        }
        else if (std::isalpha(c)) {
            tokens.push_back(readIdentifier());
        }
        else if (c == '=') {
            advance();
            tokens.push_back({TokenType::EQUAL, "="});
        }
        else {
            tokens.push_back({TokenType::UNKNOWN, std::string(1, advance())});
        }
    }

    tokens.push_back({TokenType::EOF_TOKEN, ""});
    return tokens;
}
