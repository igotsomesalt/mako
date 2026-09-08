#include <runtime.h>

namespace mako {
    Result Runtime::add_node(const std::string& name) {
        std::unique_ptr<Node> node = nodeRegistry.create(name);

        if (node == nullptr) {
            return {
                .exit_code = 0,
                .success = 0,
                .err_msg = std::format("Unknown node '{}'", name),
                .msg = ""
            };
        }

        return add_node(std::move(node));
    }

    Result Runtime::add_node(std::unique_ptr<Node> node) {
        uint32_t nodeId = graph.add_node(std::move(node));

        return {
            .exit_code = 0, 
            .success = 1, 
            .err_msg = "", 
            .msg = std::format(
                "The node ID has been automatically assigned\n\tNode ID: {}", 
                nodeId
            )
        };
    };
}