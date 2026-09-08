#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <expected>
#include <span>
#include <node.h>

namespace mako {

	
	// Represents a connection between two nodes through channels. 
	struct Edge {
		Id originNodeId;
		ChannelId originChannelId;

		Id destNodeId;
		ChannelId destChannelId;

		auto operator<=>(const Edge&) const = default;
	};


	enum class GraphErrorCode : uint8_t {
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
		
		Id nextId = 0;

		std::unordered_map<Id, std::unique_ptr<Node>> nodes;

		std::vector<std::unique_ptr<Edge>> edges;
		std::unordered_map<Edge*, size_t> edgeIndex;

		std::unordered_map<Id, std::vector<Edge*>> incoming;
		std::unordered_map<Id, std::vector<Edge*>> outgoing;

	public:
		Graph() : nodes(), outgoing(), incoming() {};
		~Graph() = default;

		// Adds a node to the graph.
		Id add_node(std::unique_ptr<Node>);

		// Removes a node from the graph.
		std::expected<void, GraphErrorCode> remove_node(Id);

		// Connects two nodes through input/output channels.
		std::expected<void, GraphErrorCode> add_edge(Edge);

		// Removes a connection between two nodes.
		std::expected<void, GraphErrorCode> remove_edge(Edge);

		// Returns all edges that define the nodeId as the destination.
		std::expected<std::span<Edge* const>, GraphErrorCode> get_input_edges(Id) const;

		// Returns all edges that define the nodeId as the origin.
		std::expected<std::span<Edge* const>, GraphErrorCode> get_output_edges(Id) const;

		// Returns true if the graph contains the node despite a could be 
		// lack of connection between other nodes.
		bool contains(Id) const;

		// Returns true if start can reach target in any capacity.
		bool is_reachable(Id start, Id target) const;
	};
}