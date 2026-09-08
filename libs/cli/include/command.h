#pragma once

#include <string>
#include <vector>
#include <memory>
#include <ostream>
#include <span>
#include <token.h>
#include <runtime.h>

namespace mako {

     // Execution context.
    class CommandExecutionContext {
    private:
        Runtime& _runtime;
        std::ostream& _out;
        std::ostream& _err;

    public:
        CommandExecutionContext(
            Runtime& runtime,
            std::ostream& out,
            std::ostream& err
        ) : _runtime(runtime), _out(out), _err(err) {}

        inline Runtime& runtime() {
            return _runtime;
        }

        inline std::ostream& out() {
            return _out;
        }

        inline std::ostream& err() {
            return _err;
        }
    };

    // ______________________________________________________________________
    // An executable command interface that defines an execution contract
    // as well as metadata contracts.
    class Command {
    protected:
        const std::string _name;
        const std::string _description;
        const std::string _usage;
        std::span<Token> args;

    public:

        Command(const std::string& name, const std::string& description, const std::string& usage) :
            _name(std::move(name)), 
            _description(std::move(description)), 
            _usage(std::move(usage)) {}
        virtual ~Command() = default;

        // Command metadata
        inline const std::string& name() const {
            return _name;
        };

        inline const std::string& description() const {
            return _description;
        };
     
        inline const std::string& usage() const {
            return _usage;
        };

        // Execute the command.
        virtual int execute(CommandExecutionContext&) = 0;

        inline void set_args(std::span<Token> args) {
            this->args = args;
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

        int execute(CommandExecutionContext&) override;
    };
}