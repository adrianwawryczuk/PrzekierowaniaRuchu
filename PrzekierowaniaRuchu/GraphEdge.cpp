#include "GraphEdge.h"

GraphEdge::GraphEdge(int idParm, short int directionParm, GraphNode* fromParm, GraphNode* toParm, float lengthParm): arcFlags(nullptr)
{
	id = idParm;
	direction = directionParm;
	from = fromParm;
	to = toParm;
	length = lengthParm;
}

GraphEdge::GraphEdge(int, short int, GraphNode* from, GraphNode* to, vector<bool>*): id(0), direction(0), from(nullptr), to(nullptr), arcFlags(nullptr), length(0)
{
}

GraphNode* GraphEdge::getFrom() const
{
	return from;
}

GraphNode* GraphEdge::getTo() const
{
	return to;
}

short int GraphEdge::getDirection() const
{
	return direction;
}

vector<bool>* GraphEdge::getArcFlags() const
{
	return arcFlags;
}

GraphEdge::~GraphEdge()
{
	id = 0;
	arcFlags = nullptr;
	from = nullptr;
	to = nullptr;
}

int GraphEdge::getId() const
{
	return id;
}

float GraphEdge::getLength() const
{
	return length;
}
