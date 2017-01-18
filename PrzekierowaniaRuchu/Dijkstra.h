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
	Dijkstra(int, int, bool);
	~Dijkstra();

	pair<float, list<GraphEdge*>> normalDijkstra();
	
private:
	int startNodeId, endNodeId;
	float result = 0;
	bool setArcFlags;

	Graph* graph = Graph::getGraph();
	map<int, int>* nodePreviousNodes = new map<int, int>;
	map<int, float*>* actualNodeCostValues = new map<int, float*>;
	multimap<float, int>* nodesPriorityQueue = new multimap<float, int>;

	bool isNodeExistInMap(int) const;
	void addNode(int, float, int) const;
	void setNodeAsDone(int) const;
	void pringCostToEndNode(int, float, int) const;
	static int getEndOfTheEdge(GraphEdge*, int);
	list<GraphEdge*> returnTrackArrayAndSetArcFlag(bool);
};
