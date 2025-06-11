//
// Created by mikah on 11.06.2025.
//
#pragma once
#ifndef TOKENIZATION_H
#define TOKENIZATION_H
#include <optional>
#include <string>
#include <utility>
#include <vector>

#define ERROR_EXIT 1
#define SUCCESS_EXIT 0


enum class TokenType {
    EXIT,
    INT_LIT,
    ENDL
};

struct Token {
    TokenType type {TokenType::ENDL};
    std::optional<std::string> value {};
};

class Lexer {
public:
    explicit Lexer(std::string src):
    m_src(std::move(src)) {
    }

    [[nodiscard]] std::vector<Token> lex();

private:
    const std::string m_src;
    int m_index;

    [[nodiscard]] std::optional<char> peek(int amount = 1) const;
    char consume();

};



#endif //TOKENIZATION_H
