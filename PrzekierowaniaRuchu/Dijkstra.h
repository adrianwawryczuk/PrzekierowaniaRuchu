#pragma once

#include "Graph.h"
#include "GraphNode.h"

using namespace std;

struct costAndIsDone
{
	float cost;
	bool isDone;
};

class Dijkstra
{
public:
	Dijkstra(int, int);
	~Dijkstra();

	void normalDijkstra() const;

	private:
	int startNodeId, endNodeId;
	float result = 0;

	Graph* graph = Graph::getGraph();
	map<int, float*>* actualNodeCostValues = new map<int, float*>;
	multimap<float, int>* nodesPriorityQueue = new multimap<float, int>;

	bool isNodeExistInMap(int) const;
	void addNode(int, float) const;
	void setNodeAsDone(int) const;
	void pringCostToEndNode(int, float, int) const;
	static int getEndOfTheEdge(GraphEdge*, int);
};
