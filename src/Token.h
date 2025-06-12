//
// Created by mikah on 12.06.2025.
//
#pragma once

#ifndef TOKEN_H
#define TOKEN_H
#include <optional>
#include <string>

enum class TokenType { EXIT, INT_LIT, ENDL };

struct Token {
    TokenType type{TokenType::ENDL};
    std::optional<std::string> value{};
};

#endif //TOKEN_H
