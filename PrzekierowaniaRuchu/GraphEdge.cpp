#include "GraphEdge.h"

GraphEdge::GraphEdge(int idParm, short int directionParm, GraphNode* fromParm, GraphNode* toParm, float lengthParm, string arcFlagsString)
{
	id = idParm;
	direction = directionParm;
	from = fromParm;
	to = toParm;
	length = lengthParm;
	arcFlags = new bool[arcFlagsString.length()];

	for(auto index = 0; index < arcFlagsString.length(); index++)
	{
		arcFlags[index] = 0;
	}
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

bool* GraphEdge::getArcFlags() const
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

void GraphEdge::setArcFlag(int partitionNumber) const
{
	arcFlags[partitionNumber] = true;
}
