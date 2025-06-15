//
// Created by mikah on 11.06.2025.
//

#include "Ast.h"

#include <iostream>
#include <ostream>

std::optional<Node::EXPR> Ast::parse_expr() {
    if (nextToken().has_value() && nextToken().value().type == TokenType::INT_LIT) {
        return Node::EXPR {supply()};
    }
    return std::nullopt;
}

std::optional<Node::EXIT> Ast::parse() {
    std::optional<Node::EXIT> exit;
    while (nextToken().has_value()) {
        if (nextToken().value().type == TokenType::EXIT) {
            supply();
            if (std::optional<Node::EXPR> node_expr = parse_expr(); node_expr.has_value()) {
                exit = Node::EXIT {node_expr.value()};
            } else {
                std::cerr << "No valid expression" << std::endl;
                std::exit(EXIT_FAILURE);
            }
            if (nextToken().has_value() && nextToken().value().type == TokenType::ENDL) {
                supply();
            } else {
                std::cerr << "???" << std::endl;
                std::exit(EXIT_FAILURE);
            }
        }
    }
    m_index = 0;

    return exit;
}

std::optional<Token> Ast::nextToken(const int amount) const {
    if (m_index + amount > m_tokens.size()) {
        return std::nullopt;
    }
    return m_tokens.at(m_index);
}

Token Ast::supply() {
    m_index++;
    return m_tokens.at(m_index - 1);
}
