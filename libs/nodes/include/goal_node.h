#pragma once

#include <node.h>

namespace mako::node {

	// ______________________________________________________________________
	// Entry point for graph construction. The GoalNode captures the user's
	// intent and establishes the highest-level semantic context for the graph.
	// All downstream nodes derive their purpose, constraints, and requirements
	// from this node.
	//
	// During the build phase, the AI uses this node to understand what system
	// the user wants to create and expands the graph recursively until reaching
	// executable primitives.
	class GoalNode : public Node {

	private:
		std::string instruction;

	public:
		explicit GoalNode(std::string _instruction) : instruction(std::move(_instruction)) {}
		~GoalNode() = default;

		inline constexpr Schema schema() const override {
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
						.name = "user goal",
						.description = "A description of what the user hopes to accomplish.",
						.required = true,
						.inferable = false,
						.defaultValue = std::nullopt,
						.prompt = ""
					}
				},
			};
		}
	};
}