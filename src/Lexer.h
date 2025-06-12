//
// Created by mikah on 11.06.2025.
//
#pragma once
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "Token.h"

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
