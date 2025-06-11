//
// Created by mikah on 11.06.2025.
//

#include "Tokenization.h"

#include <iostream>
#include <optional>

std::vector<Token> Lexer::lex() {
    std::vector<Token> tokens {};

    std::string buf {};

    while (nextChar().has_value()) {
        //Always has value so no issue
        if (std::isalpha(nextChar().value())) {
            buf.push_back(consume());
            while (nextChar().has_value() && std::isalnum(nextChar().value())) {
                buf.push_back(consume());
            }
            if (buf == "exit") {
                tokens.push_back(Token {TokenType::EXIT, std::nullopt});
                buf.clear();
            } else {
                std::cerr << "Kein Exit :(" << std::endl;
                std::exit(ERROR_EXIT);
            }

        }
        else if (std::isdigit(nextChar().value())) {
            buf.push_back(consume());
            while (nextChar().has_value() && std::isdigit(nextChar().value())) {
                buf.push_back(consume());
            }
            tokens.push_back(Token {TokenType::INT_LIT, buf});
            buf.clear();
        }
        else if (nextChar().has_value() && nextChar().value() == '$') {
            tokens.push_back(Token {TokenType::ENDL, std::nullopt});
            consume();
        }
        else if (nextChar().has_value() && std::isspace(nextChar().value())) {
            consume();
        }
        else {
            std::cerr << "Nicht gut" << std::endl;
            std::exit(ERROR_EXIT);
        }
    }
    m_index = 0;

    return tokens;
}

std::optional<char> Lexer::nextChar(const int peekAmount) const {
    if (m_index + peekAmount > m_src.length()) {
        return std::nullopt;
    }
    return m_src.at(m_index);
}

char Lexer::consume() {
    return m_src.at(m_index++);
}
