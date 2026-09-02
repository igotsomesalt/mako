#pragma once

#include <string>
#include <vector>
#include <memory>

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
        virtual CommandResult execute(const std::vector<std::string>& args) = 0;

    };

    // Execution context.
    class CommandExecutionContext {
    private:
        MakoRuntime* runtime;
        std::ostream* out;
        std::ostream* err;

        std::vector<std::string> args;
        bool interactive;

    public:
        inline MakoRuntime& runtime() {
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
        
        inline bool interactive() const {
            return interactive;
        }
    }

    // Adds a node to the graph.
    class AddCommand : public Command {
    public:
        
        explicit AddCommand() :
            Command(
                "add", 
                "Adds a node to the graph"
            ) {}
        ~Command() = default;

        const CommandResult execute(const CommandExecutionContext& ctx) const override;
    }
}