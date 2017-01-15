#include "Dijkstra.h"
#include <iomanip>

Dijkstra::Dijkstra(int startNodeIdP, int endNodeIdP)
{
	startNodeId = startNodeIdP;
	endNodeId = endNodeIdP;

	auto cost = 0;
	auto isDone = 0;

	actualNodeCostValues->insert(pair<int, float*>(startNodeId, new float[cost , isDone]));
	nodesPriorityQueue->insert(pair<float, int>(static_cast<float>(0.0), startNodeId));
}

Dijkstra::~Dijkstra()
{
	graph = nullptr;
}

void Dijkstra::normalDijkstra() const
{
	auto nodesToDoIterator = nodesPriorityQueue->begin();
	float actualNodeCost = 0;
	auto actualNodeId = (*nodesToDoIterator).second;
	list<GraphEdge>* listOfEdges;
	auto nodesChecked = 0;

	while (!nodesPriorityQueue->empty() && actualNodeId != endNodeId && nodesToDoIterator != nodesPriorityQueue->end())
	{
		actualNodeId = (*nodesToDoIterator).second;
		actualNodeCost = (*nodesToDoIterator).first;
		listOfEdges = graph->getNodeEdgeList(actualNodeId);

		for (auto edge : *listOfEdges)
		{
			auto directionNodeId = getEndOfTheEdge(&edge, actualNodeId);

			if (!isNodeExistInMap(directionNodeId))
			{
				addNode(directionNodeId, actualNodeCost + edge.getLength());
			}
			else
			{
				auto* node = actualNodeCostValues->find(directionNodeId)->second;
				if (node[1] == 0 && node[0] > actualNodeCost + edge.getLength())
				{
					nodesPriorityQueue->erase(nodesPriorityQueue->find(actualNodeCost));
					nodesPriorityQueue->insert(pair<float, int>(actualNodeCost + edge.getLength(), actualNodeId));
					node[0] = actualNodeCost + edge.getLength();
				}
			}
		}

		++nodesToDoIterator;
		++nodesChecked;
		setNodeAsDone(actualNodeId);
	}

	pringCostToEndNode(actualNodeId, actualNodeCost, nodesChecked);
}

int Dijkstra::getEndOfTheEdge(GraphEdge *edge, int actualNodeId)
{
	auto idTo = edge->getTo()->getId();
	if (idTo == actualNodeId)
	{
		idTo = edge->getFrom()->getId();
	}
	return idTo;
}

void Dijkstra::pringCostToEndNode(int actualNodeId, float actualNodeCost, int nodesChecked) const
{
	if (actualNodeId == endNodeId)
	{
		cout << "\nZNALEZIONO DROGE DO KONCOWEGO NODA. KOSZT: " << actualNodeCost << "\nSprawdzono wierzcholkow: " << nodesChecked << "\n";

	}
}

bool Dijkstra::isNodeExistInMap(int id) const
{
	return actualNodeCostValues->count(id) == 1;
}

void Dijkstra::addNode(int id, float lenght) const
{
	nodesPriorityQueue->insert(pair<float, int>(lenght, id));
	actualNodeCostValues->insert(pair<int, float*>(id, new float[lenght , 0]));
}

void Dijkstra::setNodeAsDone(int id) const
{
	auto* node = actualNodeCostValues->find(id)->second;
	node[1] = 1;
	nodesPriorityQueue->erase(node[0]);
}
