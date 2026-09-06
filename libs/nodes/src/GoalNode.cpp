#include <goal_node.h>

namespace mako::node {
    constexpr Schema GoalNode::schema() const {
        return {
            .name = "goal node",
            .description = "Requests information from the user.",

            .traits = {
                .deterministic = false,
                .idempotent = true,
                .cacheable = false,
                .checkpointable = true,

                .durability = DurabilityPolicy::Recoverable
            },

            .inputs = {
                {
                    .name = "goal",
                    .description = "A description of what the user hopes to accomplish.",
                    .required = true,
                    .inferable = false,
                    .defaultValue = std::nullopt,
                    .prompt = ""
                }
            },
        };
    }

    std::expected<void, ErrorCode> GoalNode::execute(ExecutionContext& ctx) {
        return {};
    }

    std::expected<void, ErrorCode> GoalNode::in(Value value) {
        if (std::holds_alternative<std::string>(value)) {
            instruction = std::get<std::string>(value);
            return {};
        }
        else return std::unexpected<ErrorCode>(ErrorCode::BadInput);
    }
}