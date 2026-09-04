#pragma once

#include <string>
#include <cstdint>

namespace mako {
    enum class TokenType : uint8_t {
        IDENTIFIER,
        STRING, NUMBER,
        DASH, DOUBLE_DASH,
        ENDLINE, UNKOWN
    };

    struct Token {
        TokenType type = TokenType::UNKOWN;
        std::string lexeme = "";
    };
}