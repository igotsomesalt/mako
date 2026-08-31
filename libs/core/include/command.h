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

    // The result of the command execution.
    struct CommandResult {
        bool success;
        int exit_code;

        std::string message;
        std::string error;
    };  
}