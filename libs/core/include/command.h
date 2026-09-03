#pragma once

#include <string>
#include <vector>
#include <memory>
#include <ostream>
#include <runtime.h>

namespace mako {

    // ______________________________________________________________________
    // An executable command interface that defines an execution contract
    // as well as metadata contracts.
    class Command {
    private:
        std::string name;
        std::string description;
        std::string usage;

    public:

        Command(const std::string& _name, const std::string& _description, const std::string& _usage) :
            name(std::move(_name)), 
            description(std::move(_description)), 
            usage(std::move(_usage)) {}
        virtual ~Command() = default;

        // Command metadata
        inline const std::string& name() const {
            return name;
        };

        inline const std::string& description() const {
            return description;
        };
     
        inline const std::string& usage() const {
            return usage;
        }

        // Execute the command.
        virtual bool execute(const CommandExecutionContext&) = 0;

    };

    // Execution context.
    class CommandExecutionContext {
    private:
        runtime::Runtime& runtime;
        std::ostream& out;
        std::ostream& err;

        const std::vector<std::string> args;
        const bool interactive;

    public:
        CommandExecutionContext(
            runtime::Runtime& _runtime,
            std::ostream& _out,
            std::ostream& _err,

            const std::vector<std::string> _args, const bool _interactive
        ) : runtime(_runtime), out(_out), err(_err), 
            args(_args), interactive(_interactive) {}

        inline const mako::runtime::Runtime& runtime() {
            return runtime;
        }

        inline std::ostream& out() {
            return out;
        }

        inline std::ostream& err() {
            return err;
        }
        
        inline const std::vector<std::string>& args() const {
            return args;
        }
        
        inline const bool interactive() const {
            return interactive;
        }
    };

    // Adds a node to the graph.
    class AddCommand : public Command {
    public:
        
        explicit AddCommand() :
            Command(
                "add", 
                "Adds a node to the graph", 
                "add <node>"
            ) {}
        ~AddCommand() = default;

        bool execute(const CommandExecutionContext&) override;
    };
}