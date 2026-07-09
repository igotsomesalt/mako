#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <expected>
#include <span>
#include <node.h>

namespace mako::graph {

	
	// Represents a connection between two nodes through channels. 
	struct Edge {
		node::Id originNodeId;
		node::ChannelId originChannelId;

		node::Id destNodeId;
		node::ChannelId destChannelId;

		auto operator<=>(const Edge&) const = default;
	};


	enum class ErrorCode : uint8_t {
		NodeNotFound,
		EdgeNotFound,
		WouldCreateCycle
	};


	// ______________________________________________________________________
	// A graph is a directed collection of nodes and edges that defines a 
	// workflow. Nodes represent individual operations, while edges represent 
	// dependencies and data flow between those operations.
	class Graph {

	private:
		
		node::Id nextId = 0;

		std::unordered_map<node::Id, std::unique_ptr<mako::node::Node>> nodes;

		std::vector<std::unique_ptr<Edge>> edges;
		std::unordered_map<Edge*, size_t> edgeIndex;

		std::unordered_map<node::Id, std::vector<Edge*>> incoming;
		std::unordered_map<node::Id, std::vector<Edge*>> outgoing;

	public:
		Graph() : nodes(), outgoing(), incoming() {};
		~Graph() = default;

		// Adds a node to the graph.
		node::Id add_node(std::unique_ptr<mako::node::Node>);

		// Removes a node from the graph.
		std::expected<void, ErrorCode> remove_node(node::Id);

		// Connects two nodes through input/output channels.
		std::expected<void, ErrorCode> add_edge(Edge);

		// Removes a connection between two nodes.
		std::expected<void, ErrorCode> remove_edge(Edge);

		// Returns all edges that define the nodeId as the destination.
		std::expected<std::span<Edge* const>, ErrorCode> get_input_edges(node::Id) const;

		// Returns all edges that define the nodeId as the origin.
		std::expected<std::span<Edge* const>, ErrorCode> get_output_edges(node::Id) const;

		// Returns true if the graph contains the node despite a could be 
		// lack of connection between other nodes.
		bool contains(node::Id) const;

		// Returns true if start can reach target in any capacity.
		bool is_reachable(node::Id start, node::Id target) const;
	};
}