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
	bool* getArcFlags() const;
	int getId() const;
	~GraphEdge();
	float getLength() const;
	void setArcFlag(int) const;

private:
	int id;
	short int direction;
	GraphNode* from;
	GraphNode* to;
	bool* arcFlags;
	float length;
};

#endif
