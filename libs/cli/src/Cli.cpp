#include <cli.h>

namespace mako {
    int CliApplication::run() {
        while (true) {
            std::cout << "> ";

            std::string input;
            if (!std::getline(std::cin, input)) break;

            auto tokens = lexer.tokenize(input);

            if (!tokens) {
                std::cout << std::format("Lexer error");
                continue;
            }

            auto command = parser.parse(*tokens);

            if (command == nullptr) {
                std::cout << std::format("Unrecognized command") << std::endl;
                continue;
            }

            command->execute(ctx);
        }

        return 0;
    }
}