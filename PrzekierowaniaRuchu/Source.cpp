#include "Header.h"

void main()
{
	Logger::getLogger().setLogLevel(Logger::TRACE);
	Logger::getLogger().Log(Logger::TRACE, "Starting program");

	//Zaladowanie bazy z pliku
	//readXmlFile("wroclaw.osm.xml");

	//Wyświetlenie obrazu krawedzi na mapie wroclawia
	//Window();

	//Obliczenie partycji i domyslnych wartosci w bazie
	//auto prep = Preparator(5, 5);

	//Wygenerowanie singletona grafu z danymi z bazy
	auto* graph = GraphCreator().createGraph();

	//Wystartowanie watkow z algorytmem dijkstry na singletonie grafu
	auto* threadGroup = new thread_group();
	threadGroup->add_thread(new thread(bind(&Dijkstra::normalDijkstra, Dijkstra(1190832828, 393835966))));
	threadGroup->add_thread(new thread(bind(&Dijkstra::normalDijkstra, Dijkstra(1190832828, 1697563536))));
	threadGroup->add_thread(new thread(bind(&Dijkstra::normalDijkstra, Dijkstra(260282239, 393835966))));
	threadGroup->add_thread(new thread(bind(&Dijkstra::normalDijkstra, Dijkstra(260282239, 1697563536))));
	threadGroup->add_thread(new thread(bind(&Dijkstra::normalDijkstra, Dijkstra(1190832828, 259421416))));
	threadGroup->join_all();

	//Wygenerowanie arcflags dla podanej ilosci partycji
	//ArcFlagsCreator();

	std::system("Pause");
}
