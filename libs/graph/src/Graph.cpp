#include <unordered_set>
#include <stack>
#include <graph.h>

namespace mako {

	Id Graph::add_node(std::unique_ptr<Node> node) {
		Id id = nextId++;

		nodes[id] = std::move(node);
		return id;
	}

	std::expected<void, GraphErrorCode> Graph::remove_node(Id nodeId) {
		int success = nodes.erase(nodeId);
		if (!success) return std::unexpected(GraphErrorCode::NodeNotFound);
		incoming.erase(nodeId);
		outgoing.erase(nodeId);
		return {};
	}

	std::expected<void, GraphErrorCode> Graph::add_edge(Edge edge) {
		if (!contains(edge.originNodeId) || !contains(edge.destNodeId)) {
			return std::unexpected(GraphErrorCode::NodeNotFound);
		}

		if (is_reachable(edge.destNodeId, edge.originNodeId)) {
			return std::unexpected(GraphErrorCode::WouldCreateCycle);
		}

		edges.push_back(std::make_unique<Edge>(edge));

		Edge* ptr = edges.back().get();
		
		edgeIndex[ptr] = edges.size() - 1;

		incoming[edge.destNodeId].push_back(ptr);
		outgoing[edge.originNodeId].push_back(ptr);

		return {};
	}

	std::expected<void, GraphErrorCode> Graph::remove_edge(Edge edge) {
		Edge* ptr = nullptr;

		for (Edge* candidate : outgoing[edge.originNodeId])
		{
			if (*candidate == edge)
			{
				ptr = candidate;
				break;
			}
		}

		if (!ptr) return std::unexpected(GraphErrorCode::EdgeNotFound);
		return {};
	}

	std::expected<std::span<Edge* const>, GraphErrorCode> Graph::get_input_edges(Id nodeId) const {
		auto node = nodes.find(nodeId);
		if (node == nodes.end()) return std::unexpected(GraphErrorCode::NodeNotFound);

		auto it = incoming.find(nodeId);
		if (it == incoming.end()) return std::span<Edge* const>{};

		return std::span<Edge* const>(it->second);
	};

	std::expected<std::span<Edge* const>, GraphErrorCode> Graph::get_output_edges(Id nodeId) const {
		auto node = nodes.find(nodeId);
		if (node == nodes.end()) return std::unexpected(GraphErrorCode::NodeNotFound);

		auto it = outgoing.find(nodeId);
		if (it == outgoing.end()) return std::span<Edge*>{};

		return std::span<Edge* const>(it->second);
	};

	bool Graph::contains(Id nodeId) const {
		return nodes.contains(nodeId);
	}

	bool Graph::is_reachable(Id start, Id target) const {
		std::unordered_set<Id> visited;
		std::stack<Id> stack;

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
				for (const Edge* next : *children) {
					stack.push(next->destNodeId);
				}
			}
		}

		return false;
	}
}
