#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <vector>
//
// Created by mikah on 06.06.2025.
//

#include <algorithm>

#include "Lexer.h"
#include "Ast.h"
#include "Generator.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Falsche Argumente" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::string content;
  {
    std::stringstream content_stream;
    std::fstream input(argv[1], std::ios::in);
    content_stream << input.rdbuf();
    content = content_stream.str();
  }

  Lexer lexer(std::move(content));
  std::vector<Token> tokens = lexer.lex();
  Ast ast(std::move(tokens));

    if (auto temp = ast.parse(); temp.has_value()) {
      Generator generator(temp.value());
      std::fstream output("./examples/basic.asm", std::ios::out);
      output << generator.generate();
    }


  return EXIT_SUCCESS;
}
