#pragma once

#ifndef BAR_H
#define BAR_H

#include <vector>

using namespace std;

class GraphNode;

class GraphEdge
{
public:
	GraphEdge(int, short int, GraphNode*, GraphNode*, float);
	GraphEdge(int, short int, GraphNode* from, GraphNode* to, vector<bool>*);
	GraphNode* getFrom() const;
	GraphNode* getTo() const;
	short int getDirection() const;
	vector<bool>* getArcFlags() const;
	int getId() const;
	~GraphEdge();
	float getLength() const;
private:
	int id;
	short int direction;
	GraphNode* from;
	GraphNode* to;
	vector<bool>* arcFlags;
	float length;
};

#endif
