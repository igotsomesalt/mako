#include <command_parser.h>

namespace mako {

    std::unique_ptr<Command> CommandParser::parse(std::span<Token> tokens) {
        if (tokens.empty()) return nullptr;
        current = &tokens[0];

        if (current->type != TokenType::IDENTIFIER) return nullptr;
        std::unique_ptr cmd = cmdRegistry->create(current->lexeme);
        if (cmd == nullptr) return nullptr;

        if (size_t size = tokens.size(); size > 1) cmd->set_args(tokens.subspan(1));

        return cmd;
    }
}