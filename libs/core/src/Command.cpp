#include <command.h>

namespace mako {

    cosnst CommandResult AddCommand::execute(const CommandExecutionContext& ctx) const override {
        return { true, 0, "", ""};
    }
}