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

    inline std::string_view token_type_name(TokenType type) {
        switch (type) {
            case TokenType::IDENTIFIER: return "identifier";
            case TokenType::NUMBER:     return "number";
            case TokenType::STRING:     return "string";
            case TokenType::DASH:       return "dash";
            case TokenType::DOUBLE_DASH:return "double dash";
            case TokenType::ENDLINE:    return "end line";
        }

    return "UNKNOWN";
}

    struct Token {
        TokenType type = TokenType::UNKOWN;
        std::string lexeme = "";
    };
}