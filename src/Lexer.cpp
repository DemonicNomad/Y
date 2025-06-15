//
// Created by mikah on 11.06.2025.
//

#include "Lexer.h"

#include <iostream>
#include <optional>

std::vector<Token> Lexer::lex() {
  std::vector<Token> tokens{};

  std::string buf{};

  while (nextChar().has_value()) {
    // Always has value so no issue
    if (std::isalpha(nextChar().value())) {
      buf.push_back(supply());
      while (nextChar().has_value() && std::isalnum(nextChar().value())) {
        buf.push_back(supply());
      }
      if (buf == "exit") {
        tokens.emplace_back(TokenType::EXIT, std::nullopt);
        buf.clear();
      }
      else {
        std::cerr << "Kein Exit :(" << std::endl;
        std::exit(EXIT_FAILURE);
      }
    }
    else if (std::isdigit(nextChar().value())) {
      buf.push_back(supply());
      while (nextChar().has_value() && std::isdigit(nextChar().value())) {
        buf.push_back(supply());
      }
      tokens.emplace_back(TokenType::INT_LIT, buf);
      buf.clear();
    }
    else if (nextChar().has_value() && nextChar().value() == '$') {
      tokens.emplace_back(TokenType::ENDL, std::nullopt);
      supply();
    }
    else if (nextChar().has_value() && std::isspace(nextChar().value())) {
      supply();
    }
    else {
      std::cerr << "Nicht gut" << std::endl;
      std::exit(EXIT_FAILURE);
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

char Lexer::supply() {
  m_index++;
  return m_src.at(m_index - 1);
}
