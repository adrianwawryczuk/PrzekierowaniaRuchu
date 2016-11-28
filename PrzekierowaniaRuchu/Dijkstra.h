#pragma once

#include "Graph.h"
#include "GraphNode.h"
#include <limits>

using namespace std;

class costAndIsDone {
public:
	float cost;
	bool isDone;
	costAndIsDone(float a, bool b) {
		cost = a;
		isDone = b;
	}
};

class Dijkstra
{
public:
	Dijkstra(Graph *, int, int);

	int normalDijkstra();
	~Dijkstra();
private:
	int startNodeId, endNodeId;
	float result = 0;
	Graph *graph;
	map<int, costAndIsDone*> *nodeCostValues = new map<int, costAndIsDone*>;
	multimap<float, int> *nodesToDo = new multimap<float, int>;
	multimap<float, int>::iterator nodesToDoIterator;
	bool isNodeDone(int id);
	bool isNodeExistInMap(int id);
	void prepareFirstSteps();
	void addNodeToCostMap(int id, float);
	void setNodeAsDone(int id);
};

