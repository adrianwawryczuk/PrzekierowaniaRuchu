#include "Graph.h"

Graph::Graph() {
	graph = new map<int, GraphNode>;
}

Graph::~Graph() {
	graph = nullptr;
}

void Graph::addNode(GraphNode node) {
	graph->insert({ node.getId(), node });
}

void Graph::addEdgeToNodes(GraphEdge edge) {
	edge.getFrom()->putEdge(edge);
	edge.getTo()->putEdge(edge);
}

bool isEdgeInversed(GraphEdge *edge) {
	if (edge->getDirection() == -1) {
		return true;
	}
	else {
		return false;
	}
}

GraphNode* Graph::getNode(int nodeId) {
	return &graph->at(nodeId);
}