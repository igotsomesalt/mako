#include <command_lexer.h>

namespace mako {
    std::optional<std::vector<Token>> CommandLexer::tokenize(std::string& command) {
        src = command;
        current = src.data();
        end = current + src.size();
        
        while (current != end) {
                 if (std::isalpha(*current))    resolve_alpha();
            else if (std::isdigit(*current))    resolve_digit(); 
            else if (*current == '-')           resolve_dash(); 
            else if (*current == ' ')           current++;
            else return std::nullopt;
        }

        tokens.push_back({.type = TokenType::ENDLINE });

        return tokens;
    }

    void CommandLexer::resolve_alpha() {
        char* start = current;
        
        while (std::isalpha(*current) || std::isdigit(*current)) {
            current++;
        }

        tokens.push_back({
            .type = TokenType::IDENTIFIER,
            .lexeme = std::string(start, current)
        });
    }

    void CommandLexer::resolve_digit() {
        char* start = current;
        int dots = 0;

        while (std::isdigit(*current) || *current == '.' || dots <= 1) {
            if (*current == '.') current++;
            current++;
        }

        tokens.push_back({
            .type = TokenType::NUMBER,
            .lexeme = std::string(start, current)
        });
    }

    void CommandLexer::resolve_dash() {
        if (*(++current) == '-') {
            tokens.push_back({
                .type = TokenType::DOUBLE_DASH
            });

            current++;
        }

        tokens.push_back({
            .type = TokenType::DASH
        });
    }
}