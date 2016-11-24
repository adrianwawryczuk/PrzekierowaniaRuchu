#include "XmlReader.h"
#include "Logger.h"
#include "Window.h"
#include "GraphCreator.h"
#include "Preparator.h"

using namespace std;

void main() {

	Logger::getLogger().setLogLevel(Logger::TRACE);
	Logger::getLogger().Log(Logger::TRACE, "Starting program");
	
	//readXmlFile("wroclaw.osm.xml");
	
	//Window();

	//Preparator prep = Preparator(5, 5);

	GraphCreator graphCreator = GraphCreator();
	Graph *graph = graphCreator.getGraph();

	GraphEdge *edge = &graph->getNode(145728120)->getEdgeList()->front();

	cout << edge->getId() << edge->getLength() << endl;

	std::system("PAUSE");

}

