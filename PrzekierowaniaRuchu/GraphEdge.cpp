#include "GraphEdge.h"

GraphEdge::GraphEdge(int idParm, short int directionParm, GraphNode* fromParm, GraphNode* toParm, float lengthParm) {
	id = idParm;
	direction = directionParm;
	from = fromParm;
	to = toParm;
	length = lengthParm;
}

GraphEdge::GraphEdge(int, short int, GraphNode* from, GraphNode* to, vector<bool>*) {

}

GraphNode* GraphEdge::getFrom() {
	return from;
}

GraphNode* GraphEdge::getTo() {
	return to;
}

short int GraphEdge::getDirection() {
	return direction;
}

vector<bool>* GraphEdge::getArcFlags() {
	return arcFlags;
}

GraphEdge::~GraphEdge() {
	id = 0;
	arcFlags = nullptr;
	from = nullptr;
	to = nullptr;
}

int GraphEdge::getId() {
	return id;
}

float GraphEdge::getLength() {
	return length;
}