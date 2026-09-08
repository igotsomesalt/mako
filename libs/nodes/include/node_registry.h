#pragma once

#include <unordered_map>
#include <memory>
#include <functional>
#include <node.h>

namespace mako {

    class NodeRegistry {

    private:
        using Factory = std::function<std::unique_ptr<Node>()>;
        std::unordered_map<std::string, Factory> nodes;

    public:
        template<typename T>
        inline void register_node(const std::string& key) {
            nodes[key] = [] {
                return std::make_unique<T>();
            };
        }

        inline std::unique_ptr<Node> create(const std::string& key) const {
            auto it = nodes.find(key);
            if (it == nodes.end()) return nullptr;
            return it->second();
        }
    };
}