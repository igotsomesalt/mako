#pragma once

#include <vector>
#include <string>
#include <optional>
#include <cstdlib>
#include <cctype>
#include <Token.h>

namespace mako {

    class CommandLexer {

    private:
        std::string src;

        char* current;
        char* end;

        std::vector<Token> tokens;

        void resolve_alpha();
        void resolve_digit();
        void resolve_dash();

    public:
        explicit CommandLexer() : src(), current(), end() {}

        inline ~CommandLexer() {
            delete current;
            delete end;
        }

        std::optional<std::vector<Token>> tokenize(std::string& command);
    };
}