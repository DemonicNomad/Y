#pragma once

//
// Created by mikah on 11.06.2025.
//

#include "Nodes.h"
#include <vector>

class Ast {
public:
    explicit Ast(std::vector<Token> tokens):
    m_tokens(std::move(tokens)) {}

    std::optional<Node::EXIT> parse();
private:
    const std::vector<Token> m_tokens {};
    int m_index {};

    std::optional<Node::EXPR> parse_expr();

    [[nodiscard]] std::optional<Token> nextToken(const int amount = 1) const;

    Token supply();
};
