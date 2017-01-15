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
	Dijkstra(Graph*, int, int);
	~Dijkstra();

	void normalDijkstra() const;

private:
	int startNodeId, endNodeId;
	float result = 0;

	Graph* graph;
	map<int, float*>* actualNodeCostValues = new map<int, float*>;
	multimap<float, int>* nodesPriorityQueue = new multimap<float, int>;

	bool isNodeExistInMap(int id) const;
	void addNode(int id, float) const;
	void setNodeAsDone(int id) const;
	void pringCostToEndNode(int, float, int) const;
	static int getEndOfTheEdge(GraphEdge *edge, int actualNodeId);
};
