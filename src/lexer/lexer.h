#pragma once
#include <string>
#include <vector>

enum class TokenType {
    PRINT,
    STRING,
    EOF_TOKEN,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string lexeme;
};

class Lexer {
public:
    explicit Lexer(const std::string& source);

    std::vector<Token> tokenize();

private:
    std::string source;
    size_t pos = 0;

    char peek() const;
    char advance();
    void skipWhitespace();

    Token readString();
    Token readIdentifier();
};
