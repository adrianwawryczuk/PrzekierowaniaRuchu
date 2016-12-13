#include "GraphNode.h"
#include "GraphEdge.h"

GraphNode::GraphNode(int idParm, int partitionNumberParm)
{
	id = idParm;
	partitionNumber = partitionNumberParm;
	edgeList = new list<GraphEdge>;
}

int GraphNode::getId() const
{
	return id;
}

int GraphNode::getPartitionNumber() const
{
	return partitionNumber;
}

void GraphNode::putEdge(GraphEdge edge) const
{
	edgeList->push_back(edge);
}

list<GraphEdge>* GraphNode::getEdgeList() const
{
	return edgeList;
}
