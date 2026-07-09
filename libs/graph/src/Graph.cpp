#include <unordered_set>
#include <stack>
#include <graph.h>

namespace mako {

	node::Id graph::Graph::add_node(std::unique_ptr<node::Node> node) {
		node::Id id = nextId++;

		nodes[id] = std::move(node);
		return id;
	}

	std::expected<void, graph::ErrorCode> graph::Graph::remove_node(node::Id nodeId) {
		int success = nodes.erase(nodeId);
		if (!success) return std::unexpected(graph::ErrorCode::NodeNotFound);
		incoming.erase(nodeId);
		outgoing.erase(nodeId);
		return {};
	}

	std::expected<void, graph::ErrorCode> graph::Graph::add_edge(Edge edge) {
		if (!contains(edge.originNodeId) || !contains(edge.destNodeId)) {
			return std::unexpected(ErrorCode::NodeNotFound);
		}

		if (is_reachable(edge.destNodeId, edge.originNodeId)) {
			return std::unexpected(ErrorCode::WouldCreateCycle);
		}

		edges.push_back(std::make_unique<Edge>(edge));

		Edge* ptr = edges.back().get();
		
		edgeIndex[ptr] = edges.size() - 1;

		incoming[edge.destNodeId].push_back(ptr);
		outgoing[edge.originNodeId].push_back(ptr);

		return {};
	}

	std::expected<void, graph::ErrorCode> graph::Graph::remove_edge(Edge edge) {
		Edge* ptr = nullptr;

		for (Edge* candidate : outgoing[edge.originNodeId])
		{
			if (*candidate == edge)
			{
				ptr = candidate;
				break;
			}
		}

		if (!ptr) return std::unexpected(ErrorCode::EdgeNotFound);
		return {};
	}

	std::expected<std::span<graph::Edge* const>, graph::ErrorCode> graph::Graph::get_input_edges(node::Id nodeId) const {
		auto node = nodes.find(nodeId);
		if (node == nodes.end()) return std::unexpected(ErrorCode::NodeNotFound);

		auto it = incoming.find(nodeId);
		if (it == incoming.end()) return std::span<Edge* const>{};

		return std::span<graph::Edge* const>(it->second);
	};

	std::expected<std::span<graph::Edge* const>, graph::ErrorCode> graph::Graph::get_output_edges(node::Id nodeId) const {
		auto node = nodes.find(nodeId);
		if (node == nodes.end()) return std::unexpected(ErrorCode::NodeNotFound);

		auto it = outgoing.find(nodeId);
		if (it == outgoing.end()) return std::span<graph::Edge*>{};

		return std::span<graph::Edge* const>(it->second);
	};

	bool graph::Graph::contains(node::Id nodeId) const {
		return nodes.contains(nodeId);
	}

	bool graph::Graph::is_reachable(node::Id start, node::Id target) const {
		std::unordered_set<node::Id> visited;
		std::stack<node::Id> stack;

		stack.push(start);

		// Create a stack to traverse tree.
		while (!stack.empty()) {

			// Pop to current;
			auto current = stack.top();
			stack.pop();

			// Check base case.
			if (current == target) return true;

			// Return to top of loop if the current node has been vistited.
			if (visited.contains(current)) continue;

			visited.insert(current);

			// Push children to stack.
			auto children = get_output_edges(current);
			if (children) {
				for (const graph::Edge* next : *children) {
					stack.push(next->destNodeId);
				}
			}
		}

		return false;
	}
}
