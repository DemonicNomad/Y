//
// Created by mikah on 12.06.2025.
//
#pragma once

#include <optional>
#include <string>

enum class TokenType { EXIT, INT_LIT, ENDL, OPEN_PAREN, CLOSE_PAREN };

struct Token {
    TokenType type{TokenType::ENDL};
    std::optional<std::string> value{};
};
