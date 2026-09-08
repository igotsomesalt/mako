#pragma once

#include <node.h>

namespace mako {

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
		explicit GoalNode() : instruction() {}
		~GoalNode() override = default;

		constexpr Schema schema() const override;
		std::expected<void, ErrorCode> execute(ExecutionContext& ctx) override;
		std::expected<void, ErrorCode> in(Value value) override;
	};
}