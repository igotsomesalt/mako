#include <runtime.h>

namespace mako {
    runtime::Result runtime::Runtime::add_node(std::unique_ptr<node::Node> node) {
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