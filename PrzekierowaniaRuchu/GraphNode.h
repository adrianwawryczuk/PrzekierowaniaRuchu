#pragma once

#ifndef FOO_H
#define FOO_H

#include <list>
#include <iostream>

using namespace std;

class GraphEdge;

class GraphNode
{
public:
	GraphNode(int, int);
	~GraphNode();
	int getId();
	int getPartitionNumber();
	void putEdge(GraphEdge);
	list<GraphEdge>* getEdgeList();

private:
	int id;
	int partitionNumber;
	list<GraphEdge> *edgeList;
};

#endif
