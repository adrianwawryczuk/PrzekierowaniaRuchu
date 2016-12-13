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
	int getId() const;
	int getPartitionNumber() const;
	void putEdge(GraphEdge) const;
	list<GraphEdge>* getEdgeList() const;

private:
	int id;
	int partitionNumber;
	list<GraphEdge>* edgeList;
};

#endif
