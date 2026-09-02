#pragma once

#include <format>
#include <node.h>
#include <graph.h>

namespace mako::runtime {

    struct Result {
        int exit_code;
        bool success;

        std::string err_msg;
        std::string msg;
    };

    class Runtime {
    private:
        mako::graph::Graph graph;

    public:
        inline Runtime() : graph() {}

        Result add_node(std::unique_ptr<mako::node::Node> node);
    };
}