#pragma once

#include <variant>
#include <expected>
#include <optional>
#include <unordered_map>
#include <string>
#include <memory>
#include <cstdint>
#include <vector>

namespace mako {


    using Id = uint32_t;
    using ChannelId = uint32_t;


    // Native primitive data types.
    using Value = std::variant<
        std::string,
        int,
        float,
        bool
    >;

    
    // Error type returned by the node.
    enum class ErrorCode : uint8_t {
        ExecutionFailed,
        InitializationFailed,
        ShutdownFailed,
        RecoveryFailed,
        MissingInput,
        BadInput
    };

    
    // ______________________________________________________________________
    // Holds context for execution owned by runtime; the origin, the
    // destination, and the output data. This is a memory retrieval contract
    // that must be implemented by all heirs.
    //
    // Thread-safety: implementations are assumed to be exclusive to a single
    // executing node at a time. If the runtime shares a context across
    // concurrently-executing nodes, the implementation must provide its own
    // synchronization; this base class makes no such guarantee.
    class ExecutionContext {

    protected:
        const Id currentNode;

    public:

        ExecutionContext(Id _currentNode) : currentNode(_currentNode) {};
        virtual ~ExecutionContext() = default;

        // ______________________________________________________________________
        // Returns a shared pointer to data owned by the execution context. The
        // pointer is valid whether or not the current execution context exists.
        virtual std::expected<std::shared_ptr<const Value>, ErrorCode> input(ChannelId) = 0;

        // Publishes output into the execution context on the given channel.
        // Single overload taking Value by value: pass an rvalue to move in,
        // pass an lvalue to copy in. Avoids paying for a copy on the move path.
        virtual std::expected<void, ErrorCode> output(ChannelId, std::shared_ptr<Value> value) = 0;
    };
    

    // ______________________________________________________________________
    // Determines what if and what type of recovery needs to occur after the
    // an unexpected closure of the application.
    enum class DurabilityPolicy : uint8_t {
        None,
        Restartable,
        Recoverable
    };


    // Traits of the node.
    struct Traits {
        bool deterministic;
        bool idempotent;
        bool cacheable;
        bool checkpointable;

        DurabilityPolicy durability;
    };

    // ______________________________________________________________________
    // Describes a single property that a node accepts or produces.
    //
    // Property schemas define the semantic contract for a value, including 
    // its purpose, whether it must be provided by the user, whether the AI 
    // may infer it from available context, any default value, and the prompt 
    // used to request the information when it cannot be determined 
    // automatically.
    struct PropertySchema {
        std::string name;
        std::string description;

        bool required;
        bool inferable;

        std::optional<Value> defaultValue;

        std::string prompt;
    };


    // ______________________________________________________________________
    // Describes the interface and behavior of a node type.
    //
    // A node schema specifies the semantic contract between the node and the 
    // rest of the graph. It defines the information the node requires 
    // (inputs), the information it produces (outputs), and the metadata 
    // needed for the AI to construct, validate, and execute graphs while 
    // interacting with the user.
    struct Schema {
        std::string name;
        std::string description;
        Traits traits;

        std::vector<PropertySchema> inputs;
    };
        
    
    // ______________________________________________________________________
    // Represents a single executable operation in a graph.
    //
    // Nodes define one step of a pipeline. They receive data through input
    // channels, perform some work, and publish results through output 
    // channels. The runtime executes nodes once all of their dependencies 
    // have been satisfied.
    class Node {

    public:

        Node() = default;
        virtual ~Node() = default;

        // Returns the semantic contract for a node type.
        virtual constexpr Schema schema() const = 0;

        // Called prior to execution to initialize internal state.
        virtual std::expected<void, ErrorCode> initialize() { return {}; }

        // Executes node.
        virtual std::expected<void, ErrorCode> execute(ExecutionContext&) = 0;

        // Called after execution to shutsdown internal state.
        virtual std::expected<void, ErrorCode> shutdown() { return {}; }

        // Called after an unexpected shutdown to restore internal state.
        virtual std::expected<void, ErrorCode> recover() { return {}; }

        // Called after internal state has been restored.
        virtual std::expected<void, ErrorCode>  resume() { return {}; }
        
        // Give input to the node.
        virtual std::expected<void, ErrorCode> in(Value) { return {}; }
    };
}