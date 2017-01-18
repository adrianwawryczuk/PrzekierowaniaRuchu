#include "ArcFlagsCreator.h"
#include <thread>

ArcFlagsCreator::ArcFlagsCreator()
{
	//wszystkie krawedzie graniczne

	auto* boudingNodes = MySqlConnection::getBoundingNodes();

	auto *graphMap = Graph::getGraph()->getMap();

	auto* threadGroup = new boost::thread_group();

	auto index = 0;

	for(auto it = graphMap->begin(); it != graphMap->end(); ++it)
	{
		while(boudingNodes->next())
		{
			Dijkstra(it->first, boudingNodes->getInt("id"), true).normalDijkstra();
		}
	}

	cout << index;
}
