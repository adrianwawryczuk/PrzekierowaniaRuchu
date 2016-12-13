#include "Header.h"

void main()
{
	Logger::getLogger().setLogLevel(Logger::TRACE);
	Logger::getLogger().Log(Logger::TRACE, "Starting program");

	//readXmlFile("wroclaw.osm.xml");
	//Window();
	//	Preparator prep = Preparator(5, 5);

	auto creator = GraphCreator();
	auto* graph = creator.createGraph();

	//Dijkstra dijkstraThread = Dijkstra(graph);

	std::system("PAUSE");
}
