#pragma once

#include <unordered_map>
#include <memory>
#include <functional>
#include <command.h>

namespace mako {

    class CommandRegistry {

    private:
        using Factory = std::function<std::unique_ptr<Command>()>;
        std::unordered_map<std::string, Factory> commands;

    public:
        template<typename T>
        inline void register_command(const std::string& key) {
            commands[key] = [] {
                return std::make_unique<T>();
            };
        }

        inline std::unique_ptr<Command> create(const std::string& key) const {
            auto it = commands.find(key);
            if (it == commands.end()) return nullptr;
            return it->second();
        }
    };
}