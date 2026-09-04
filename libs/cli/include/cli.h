#pragma once

#include <iostream>
#include <command_lexer.h>
#include <command_parser.h>
#include <command_registry.h>
#include <runtime.h>

namespace mako {

    class CliApplication {

    private:
        CommandRegistry cmds;
        CommandParser parser;
        CommandLexer lexer;
        CommandExecutionContext ctx;
        runtime::Runtime runtime;

    public:
        inline CliApplication() : cmds(), parser(cmds), lexer(), runtime(), ctx(runtime, std::cout, std::cout) {
            cmds.register_command<AddCommand>("add");
        }


        int run();
    };
}