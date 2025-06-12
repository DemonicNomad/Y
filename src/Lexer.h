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

#include "Token.h"

#define ERROR_EXIT 1
#define SUCCESS_EXIT 0

class Lexer {
public:
    explicit Lexer(std::string src) : m_src(std::move(src)) {
    }

    [[nodiscard]] std::vector<Token> lex();

private:
    const std::string m_src{};
    int m_index{};

    [[nodiscard]] std::optional<char> nextChar(int peekAmount = 1) const;

    char supply();
};

#endif  // TOKENIZATION_H
