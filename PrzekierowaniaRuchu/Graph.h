#pragma once

#include <list>
#include <map>

#include "GraphNode.h"
#include "GraphEdge.h"

using namespace std;

class Graph
{
public:
	Graph();
	~Graph();

	void addNode(GraphNode);
	void addEdgeToNodes(GraphEdge);
	GraphNode* getNode(int);
private:
	map<int, GraphNode> *graph;
};

