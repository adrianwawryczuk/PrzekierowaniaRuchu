#include "Header1.h"

void main() {

	Logger::getLogger().setLogLevel(Logger::TRACE);
	Logger::getLogger().Log(Logger::TRACE, "Starting program");
	
	//readXmlFile("wroclaw.osm.xml");
	//Window();
	//Preparator prep = Preparator(5, 5);

	Graph *graph = new GraphCreator()->getGraph();

	Dijkstra dijkstraThread = Dijkstra(&graph);

	std::system("PAUSE");

}

