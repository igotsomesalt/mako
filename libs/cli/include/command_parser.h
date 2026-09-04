#pragma once

#include <span>
#include <Token.h>
#include <Command.h>
#include <Command_registry.h>

namespace mako {

    class CommandParser {

    private:
        CommandRegistry* cmdRegistry;
        std::span<const Token> tokens;

        const Token* current;

    public:
        inline explicit CommandParser(CommandRegistry& cmdRegistry) : 
            tokens(tokens),
            cmdRegistry(&cmdRegistry) {}

        inline ~CommandParser() {
            delete current;
        }

        std::unique_ptr<Command> parse(std::span<Token> tokens);
    };
}