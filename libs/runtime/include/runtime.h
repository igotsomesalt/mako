#pragma once

#include <format>
#include <goal_node.h>
#include <node_registry.h>
#include <node.h>
#include <graph.h>

namespace mako {

    struct Result {
        int exit_code;
        bool success;

        std::string err_msg;
        std::string msg;
    };

    class Runtime {
    private:
        Graph graph;
        NodeRegistry nodeRegistry;


    public:
        Runtime() : graph(), nodeRegistry() {
            nodeRegistry.register_node<GoalNode>("goal");
        }

        Result add_node(const std::string& node);
        Result add_node(std::unique_ptr<Node> node);
    };
}