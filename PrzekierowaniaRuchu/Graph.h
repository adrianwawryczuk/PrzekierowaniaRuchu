#pragma once

#include <list>
#include <map>

#include "GraphNode.h"
#include "GraphEdge.h"

using namespace std;

class Graph
{
public:
	static Graph* getGraph()
	{
		static Graph singleton;
		return &singleton;
	}

	void addNode(GraphNode) const;
	static void addEdgeToNodes(GraphEdge);
	GraphNode* getNode(int) const;
	int getNodesCount() const;
	list<GraphEdge>* getNodeEdgeList(int) const;
	map<int, GraphNode>* getMap() const;
private:
	Graph();
	~Graph();
	map<int, GraphNode>* graph;
};
