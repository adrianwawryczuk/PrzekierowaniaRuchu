#include "GraphNode.h"
#include "GraphEdge.h"

GraphNode::GraphNode(int idParm, int partitionNumberParm) {
	id = idParm;
	partitionNumber = partitionNumberParm;
	edgeList = new list<GraphEdge>;
}

GraphNode::~GraphNode() {
}

int GraphNode::getId() {
	return id;
}

int GraphNode::getPartitionNumber() {
	return partitionNumber;
}

void GraphNode::putEdge(GraphEdge edge) {
	edgeList->push_back(edge);
}

list<GraphEdge>* GraphNode::getEdgeList() {
	return edgeList;
}
