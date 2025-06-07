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

enum class TokenType {
    RETURN,
    INT_LIT,
    ENDL
};

std::ostream& operator<<(std::ostream &os, const TokenType &t) {
    switch (t) {
        case TokenType::RETURN: os << "RETURN"; break;
        case TokenType::INT_LIT: os << "INT_LIT"; break;
        case TokenType::ENDL: os << "ENDL"; break;
    }

    return os;
}

struct Token {
    TokenType type;
    std::optional<std::string> value {};
};

//Temp
std::string tokensToASM(const std::vector<Token>& tokens) {
    std::stringstream output;

    output << "global _main\n";
    output << "section .text\n" ;
    output << "_main:\n";


    for (int i = 0; i < tokens.size(); i++) {
        const Token& token = tokens.at(i);
        if (token.type == TokenType::RETURN) {
            if (i+1 < tokens.size() && tokens[i+1].type == TokenType::INT_LIT) {
                if (i+2 < tokens.size() && tokens[i+2].type == TokenType::ENDL) {
                    output << "    mov eax, " + tokens[i+1].value.value() + '\n';
                    output << "    ret";
                }
            }
        }
    }

    return output.str();
}

std::vector<Token> lex(const std::string& input) {
    std::vector<Token> tokens {};

    std::string buf {};
    for (int i = 0; i < input.length(); i++) {
        const char temp = input.at(i);
        if (std::isalpha(temp)) {
            buf.push_back(temp);
            i++;
            while (std::isalnum(input.at(i))) {
                buf.push_back(input.at(i));
                i++;
            }
            i--;
            if (buf == "return") {
                tokens.push_back(Token{TokenType::RETURN, std::nullopt});
                buf.clear();
            } else {
                std::cerr << "Kein Return :(" << std::endl;
                std::exit(ERROR_EXIT);
            }
        }
        else if (std::isspace(temp)) {
            continue;
        }
        else if (std::isdigit(temp)) {
            buf.push_back(temp);
            i++;
            while (std::isdigit(input.at(i))) {
                buf.push_back(input.at(i));
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

void printLexOutput(const std::vector<Token>& tokens) {
    for (const auto&[type, value] : tokens) {
        std::cout << type << " " << value.value_or("No Value") << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Falsche Argumente" << std::endl;
        std::exit(ERROR_EXIT);
    }

    std::string content;
    {
        std::stringstream content_stream;
        std::fstream input(argv[1], std::ios::in);
        content_stream << input.rdbuf();
        content = content_stream.str();
    }


    std::vector<Token> tokens = lex(content);
    printLexOutput(tokens);

    std::ofstream output("./examples/basic.asm");
    output << tokensToASM(tokens);
    output.close();

    return SUCCESS_EXIT;
}
