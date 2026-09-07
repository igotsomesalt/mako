#include <format>
#include <command.h>

namespace mako {

    int AddCommand::execute(CommandExecutionContext& ctx) {
        if (args.size() == 0) {
            ctx.err() << "Missing argument" << std::endl;
            return 0;
        }

        if (TokenType t = args[0].type; t != TokenType::IDENTIFIER) {
            ctx.err() << std::format("Expected identifier but got {}", token_type_name(t)) << std::endl;
            return 0;
        }

        runtime::Result result = ctx.runtime().add_node(args[0].lexeme);
        
        if (!result.success) {
            ctx.err() << result.err_msg << std::endl;
            return 0;
        }

        ctx.out() << result.msg << std::endl;

        return 1;
    }
}