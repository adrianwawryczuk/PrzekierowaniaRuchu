#include "Dijkstra.h"

Dijkstra::Dijkstra(Graph* graphP, int startNodeIdP, int endNodeIdP)
{
	graph = graphP;
	startNodeId = startNodeIdP;
	endNodeId = endNodeIdP;
}


Dijkstra::~Dijkstra()
{
	graph = nullptr;
}

int Dijkstra::normalDijkstra()
{
	prepareFirstSteps();

	auto actualNode = 0;

	list<GraphEdge>* listOfEdges;

	while (nodesToDo->empty() || actualNode == endNodeId)
	{
		++nodesToDoIterator;

		actualNode = (*nodesToDoIterator).second;

		listOfEdges = graph->getNodeEdgeList(actualNode);

		for (GraphEdge edge : *listOfEdges)
		{
			int idTo = edge.getTo()->getId();

			if (!isNodeExistInMap(idTo))
			{
				addNodeToCostMap(idTo, edge.getLength());
			}

			if (!isNodeDone(idTo))
			{
			}
		}

		setNodeAsDone(actualNode);
	}

	Dijkstra::~Dijkstra();
	return result;
}

void Dijkstra::prepareFirstSteps()
{
	nodeCostValues->insert(pair<int, costAndIsDone*>(startNodeId, new costAndIsDone(0, false)));
	nodesToDo->insert(pair<float, int>(0.0, startNodeId));
	nodesToDoIterator = nodesToDo->begin();
}

bool Dijkstra::isNodeExistInMap(int id) const
{
	return nodeCostValues->count(id) == 1;
}

bool Dijkstra::isNodeDone(int id) const
{
	return nodeCostValues->find(id)->second->isDone;
}

void Dijkstra::addNodeToCostMap(int id, float lenght) const
{
	nodeCostValues->insert(pair<int, costAndIsDone*>(id, new costAndIsDone(lenght, false)));
}

void Dijkstra::setNodeAsDone(int id) const
{
	nodeCostValues->find(id)->second->isDone = true;
}
