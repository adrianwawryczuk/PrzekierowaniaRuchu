#include "Graph.h"

Graph::Graph()
{
	graph = new map<int, GraphNode>;
}

Graph::~Graph()
{
	graph = nullptr;
}

void Graph::addNode(GraphNode node) const
{
	graph->insert({node.getId(), node});
}

void Graph::addEdgeToNodes(GraphEdge edge)
{
	if(edge.getDirection() == 0)
	{
		edge.getFrom()->putEdge(edge);
		edge.getTo()->putEdge(edge);
	} 
	else if (edge.getDirection() == 1)
	{
		edge.getFrom()->putEdge(edge);
	}
	else
	{
		edge.getTo()->putEdge(edge);
	}
	
}

bool isEdgeInversed(GraphEdge* edge)
{
	if (edge->getDirection() == -1)
	{
		return true;
	}
	return false;
}

GraphNode* Graph::getNode(int nodeId) const
{
	if(graph->count(nodeId) > 0)
	{
		return &graph->at(nodeId);
	} 
	return nullptr;
	
}

int Graph::getNodesCount() const
{
	return static_cast<int>(graph->size());
}

list<GraphEdge>* Graph::getNodeEdgeList(int nodeId) const
{
	GraphNode* node = getNode(nodeId);
	if(node)
	{
		return node->getEdgeList();
	}
	return nullptr;
}

map<int, GraphNode>* Graph::getMap() const
{
	return graph;
}
