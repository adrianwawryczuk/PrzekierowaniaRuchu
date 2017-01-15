#include "Header.h"

void main()
{
	Logger::getLogger().setLogLevel(Logger::TRACE);
	Logger::getLogger().Log(Logger::TRACE, "Starting program");

	//readXmlFile("wroclaw.osm.xml");
	//Window();
	//Preparator prep = Preparator(5, 5);

	static GraphCreator creator;

	auto* graph = creator.createGraph();

	Dijkstra *dijkstraThread = new Dijkstra(graph, 1190832828, 393835966);
	dijkstraThread->normalDijkstra();

	std::system("PAUSE");
}
