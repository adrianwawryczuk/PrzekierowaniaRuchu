#include "Dijkstra.h"
#include <iomanip>

Dijkstra::Dijkstra(int startNodeIdP, int endNodeIdP, bool setArcs)
{
	startNodeId = startNodeIdP;
	endNodeId = endNodeIdP;
	setArcFlags = setArcs;

	actualNodeCostValues->insert(pair<int, float*>(startNodeId, new float[0, 0]));
	nodesPriorityQueue->insert(pair<float, int>(static_cast<float>(0.0), startNodeId));
	nodePreviousNodes->insert(pair<int, int>(startNodeIdP, startNodeIdP));
}

Dijkstra::~Dijkstra()
{
	graph = nullptr;
}

pair<float, list<GraphEdge*>> Dijkstra::normalDijkstra()
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
				addNode(directionNodeId, actualNodeCost + edge.getLength(), actualNodeId);
			}
			else
			{
				auto* node = actualNodeCostValues->find(directionNodeId)->second;
				if (node[1] == 0 && node[0] > actualNodeCost + edge.getLength())
				{
					nodesPriorityQueue->erase(nodesPriorityQueue->find(actualNodeCost));
					nodesPriorityQueue->insert(pair<float, int>(actualNodeCost + edge.getLength(), actualNodeId));
					node[0] = actualNodeCost + edge.getLength();
					nodePreviousNodes->insert(pair<int, int>(directionNodeId, actualNodeCost));
				}
			}
		}

		++nodesToDoIterator;
		++nodesChecked;
		setNodeAsDone(actualNodeId);
	}

	pringCostToEndNode(actualNodeId, actualNodeCost, nodesChecked);
	auto track = returnTrackArrayAndSetArcFlag(setArcFlags);
	listOfEdges = nullptr;
	return pair<float, list<GraphEdge*>>(actualNodeCost, track);
}

list<GraphEdge*> Dijkstra::returnTrackArrayAndSetArcFlag(bool setArcFlags)
{
	auto actualNodeId = endNodeId;
	list<GraphEdge*> track;
	auto partitionNumber = graph->getNode(endNodeId)->getPartitionNumber();

	do
	{
		int previousNodeId = nodePreviousNodes->find(actualNodeId)->second;

		list<GraphEdge>* actualNodeEdgeList = graph->getNodeEdgeList(previousNodeId);

		int oldId = actualNodeId;

		if(actualNodeEdgeList)
		{
			for (list<GraphEdge>::iterator edge = actualNodeEdgeList->begin(); edge != actualNodeEdgeList->end(); ++edge)
			{
				if (edge->getTo()->getId() == actualNodeId)
				{
					actualNodeId = edge->getFrom()->getId();
					track.push_back(&(*edge));

					if (setArcFlags)
					{
						(*edge).setArcFlag(partitionNumber);
					}
					break;
				}
				if (edge->getFrom()->getId() == actualNodeId)
				{
					actualNodeId = edge->getTo()->getId();
					track.push_back(&(*edge));

					if (setArcFlags)
					{
						(*edge).setArcFlag(partitionNumber);
					}
					break;
				}
			}
		} 
		else
		{
			break;
		}

		if(oldId == actualNodeId)
		{
			break;
		}
		
		actualNodeEdgeList = nullptr;
	}
	while (actualNodeId != startNodeId);

	track.reverse();

	nodePreviousNodes = nullptr;
	actualNodeCostValues = nullptr;
	nodesPriorityQueue = nullptr;

	return track;
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

void Dijkstra::addNode(int id, float lenght, int previousNode) const
{
	nodesPriorityQueue->insert(pair<float, int>(lenght, id));
	actualNodeCostValues->insert(pair<int, float*>(id, new float[lenght , 0]));
	nodePreviousNodes->insert(pair<int, int>(id, previousNode));
}

void Dijkstra::setNodeAsDone(int id) const
{
	auto* node = actualNodeCostValues->find(id)->second;
	node[1] = 1;
	nodesPriorityQueue->erase(node[0]);
}
