//
// Created by mikah on 11.06.2025.
//

#include "Tokenization.h"

#include <iostream>
#include <optional>

std::vector<Token> Lexer::lex() {
    std::vector<Token> tokens {};

    std::string buf {};

    for (int i = 0; i < m_src.length(); i++) {
        const char temp = m_src.at(i);
        if (std::isalpha(temp)) {
            buf.push_back(temp);
            i++;
            while (std::isalnum(m_src.at(i))) {
                buf.push_back(m_src.at(i));
                i++;
            }
            i--;
            if (buf == "exit") {
                tokens.push_back(Token{TokenType::EXIT, std::nullopt});
                buf.clear();
            } else {
                std::cerr << "Kein Exit :(" << std::endl;
                std::exit(ERROR_EXIT);
            }
        }
        else if (std::isspace(temp)) {
            continue;
        }
        else if (std::isdigit(temp)) {
            buf.push_back(temp);
            i++;
            while (std::isdigit(m_src.at(i))) {
                buf.push_back(m_src.at(i));
                i++;
            }
            i--;
            tokens.push_back(Token{TokenType::INT_LIT, buf});
            buf.clear();
        }
        else if (temp == '$') {
            tokens.push_back(Token{TokenType::ENDL, std::nullopt});
        }
        else {
            std::cerr << "Nicht gut" << std::endl;
            std::exit(ERROR_EXIT);
        }
    }

    return tokens;
}

std::optional<char> Lexer::peek(const int amount) const {
    if (m_index + amount >= m_src.length()) {
        return std::nullopt;
    }
    return m_src.at(m_index);
}

char Lexer::consume() {
    return m_src.at(m_index++);
}
