#pragma once

#ifndef BAR_H
#define BAR_H

#include <string>

using namespace std;

class GraphNode;

class GraphEdge
{
public:
	GraphEdge(int, short int, GraphNode* from, GraphNode* to, float, string);
	GraphNode* getFrom() const;
	GraphNode* getTo() const;
	short int getDirection() const;
	__int8* getArcFlags() const;
	int getId() const;
	~GraphEdge();
	float getLength() const;

private:
	int id;
	short int direction;
	GraphNode* from;
	GraphNode* to;
	__int8* arcFlags;
	float length;
};

#endif
