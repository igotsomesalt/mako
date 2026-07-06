#pragma once

#include <variant>
#include <expected>
#include <unordered_map>
#include <string>

namespace mako::graph {

    using NodeId = uint32_t;
    using PortId = uint32_t;

    // Native primitive data types.
    using Value = std::variant<
        std::string,
        int,
        float,
        bool
    >;
    
    // ______________________________________________________________________
    // Error type returned by node execution.
    enum class NODE_RUNTIME_ERROR_CODE : uint8_t {
        NodeExecutionFailed, 
    };
    
    // ______________________________________________________________________
    // Holds context for execution owned by runtime; the origin, the 
    // destination, and the output data.
    class ExecutionContext {
    private:
        std::unordered_map<NodeId, std::unordered_map<PortId, Value>> values;

    public:

        // Returns the input from the 
        template<typename T>
        std::expected<T, NODE_RUNTIME_ERROR_T> input(PortId);

        template<typename T>
        std::expected<void, NODE_RUNTIME_ERROR_T> output(PortId, T&& value);
    };
    
    // ______________________________________________________________________
    // Represents a single executable operation in a graph.
    //
    // Nodes define one step of a pipeline. They receive data through input
    // ports, perform some work, and publish results through output ports.
    // The runtime executes nodes once all of their dependencies have been
    // satisfied.
    struct Node {
        const NodeId id;

        explicit Node(NodeId id): id(id) {}
        virtual ~Node() = default;

        // Called prior to execution to initialize internal state.
        virtual void initialize() {}

        // Executes node.
        virtual void execute(ExecutionContext&) = 0;

        // Called after execution to shutsdown internal state.
        virtual void shutdown() {}
    };

    enum class NodeType {
        Constant, 
    };

    // **
    // Test nodes
    // **
    struct Node_Constant : public Node {
        const NodeId id;

        explicit Node_Constant(NodeId id) : Node(id) {}
        ~Node_Constant() override = default;

        void initialize() override;
        void execute(ExecutionContext&) override;
        void shutdown() override;

    };
}