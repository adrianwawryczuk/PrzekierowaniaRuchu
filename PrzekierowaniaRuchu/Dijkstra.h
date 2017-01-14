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

	int normalDijkstra() const;
	~Dijkstra();
private:
	int startNodeId, endNodeId;
	float result = 0;
	Graph* graph;
	//id, tablica
	map<int, float*>* nodeCostValues = new map<int, float*>;

	//dlugosc aktualna do tego noda, id
	multimap<float, int>* nodesToDo = new multimap<float, int>;
	bool isNotNodeDone(int id) const;
	bool isNodeExistInMap(int id) const;
	void addNode(int id, float) const;
	void setNodeAsDone(int id) const;
};
