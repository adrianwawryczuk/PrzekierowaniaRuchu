#include "Dijkstra.h"

Dijkstra::Dijkstra(Graph* graphP, int startNodeIdP, int endNodeIdP)
{
	graph = graphP;
	startNodeId = startNodeIdP;
	endNodeId = endNodeIdP;

	auto cost = 0;
	auto isDone = 0;

	nodeCostValues->insert(pair<int, float*>(startNodeId, new float[cost, isDone]));
	nodesToDo->insert(pair<float, int>(0.0, startNodeId));
}

Dijkstra::~Dijkstra()
{
	graph = nullptr;
}

int Dijkstra::normalDijkstra() const
{
	auto nodesToDoIterator = nodesToDo->begin();
	float actualNodeCost = 0;
	auto actualNodeId = (*nodesToDoIterator).second;

	auto listOfEdges = new list<GraphEdge>;

	while (!nodesToDo->empty() && actualNodeId != endNodeId && nodesToDoIterator != nodesToDo->end())
	{
		actualNodeId = (*nodesToDoIterator).second;
		actualNodeCost = (*nodesToDoIterator).first;

		listOfEdges = graph->getNodeEdgeList(actualNodeId);

		for (auto edge : *listOfEdges)
		{
			auto idTo = edge.getTo()->getId();

			if (!isNodeExistInMap(idTo) || isNotNodeDone(idTo))
			{
				//Node nie istnieje i pierwszy raz go spotykam, dodaje do kolejki
				//z  jego id i suma aktualnego noda i krawedzi
				addNode(idTo, actualNodeCost + edge.getLength());
			} else
			{
				//Node istnieje wiec trzeba sprawdzic czy jest 'zrobiony'
				//Jesli nie to mozna zwalidowac czy jego wartosc dojscia jest gorsza od proponowanej
				auto *node = nodeCostValues->find(idTo)->second;
				if(node[1] == 0 && node[0] > actualNodeCost + edge.getLength())
				{
					//Usuwam z kolejki noda i dodaje nowego w kolejce o nowym koszcie dojscia
					nodesToDo->erase(nodesToDo->find(actualNodeCost));
					nodesToDo->insert(pair<float, int>(actualNodeCost + edge.getLength(), actualNodeId));
					node[0] = actualNodeCost + edge.getLength();
				}
			}
		}

		++nodesToDoIterator;
		setNodeAsDone(actualNodeId);
	}

	cout << actualNodeCost;
	system("Pause");
	return result;
}

bool Dijkstra::isNodeExistInMap(int id) const
{
	return nodeCostValues->count(id) == 1;
}

bool Dijkstra::isNotNodeDone(int id) const
{
	return nodeCostValues->find(id)->second[1] == 1;
}

void Dijkstra::addNode(int id, float lenght) const
{
	nodesToDo->insert(pair<float, int>(lenght, id));
	nodeCostValues->insert(pair<int, float*>(id, new float[lenght, 0]));
}

void Dijkstra::setNodeAsDone(int id) const
{
	auto *node = nodeCostValues->find(id)->second;
	node[1] = true;
	nodesToDo->erase(node[0]);
}