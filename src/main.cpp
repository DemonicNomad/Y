#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <vector>
//
// Created by mikah on 06.06.2025.
//
#define ERROR_EXIT 1
#define SUCCESS_EXIT 0

#include "Lexer.h"

// Temp
std::string tokensToASM(const std::vector<Token> &tokens) {
  std::stringstream output;

  output << "global _main\n";
  output << "section .text\n";
  output << "_main:\n";

  for (int i = 0; i < tokens.size(); i++) {
    const Token &token = tokens.at(i);
    if (token.type == TokenType::EXIT) {
      if (i + 1 < tokens.size() && tokens[i + 1].type == TokenType::INT_LIT) {
        if (i + 2 < tokens.size() && tokens[i + 2].type == TokenType::ENDL) {
          output << "    mov eax, " + tokens[i + 1].value.value() + '\n';
          output << "    ret";
        }
      }
    }
  }

  return output.str();
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Falsche Argumente" << std::endl;
    std::exit(ERROR_EXIT);
  }

  std::string content; {
    std::stringstream content_stream;
    std::fstream input(argv[1], std::ios::in);
    content_stream << input.rdbuf();
    content = content_stream.str();
  } {
    Lexer lexer(std::move(content));
    std::vector<Token> tokens = lexer.lex();
    std::ofstream output("./examples/basic.asm", std::ios::out);
    output << tokensToASM(tokens);
  }

  return SUCCESS_EXIT;
}
