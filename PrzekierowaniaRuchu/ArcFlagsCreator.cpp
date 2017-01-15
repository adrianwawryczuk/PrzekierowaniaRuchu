#include "ArcFlagsCreator.h"

ArcFlagsCreator::ArcFlagsCreator()
{
	//wszystkie krawedzie graniczne

	auto* boudingNodes = MySqlConnection::getBoundingNodes();

	auto *graphMap = Graph::getGraph()->getMap();

	auto* threadGroup = new boost::thread_group();

	for(auto it = graphMap->begin(); it != graphMap->end(); ++it)
	{
		
	}
	//dla wszystkich zwyklych nodeów przejsc do nodeow granicznych,
	//jesli sie uda to wtedy z arraya krawedzi wskazujacych droge kazda z tych krawedzi dostaje parametr true dla dojscia do danej partycji
	//optymalizacja (jesli dochodzimy do krawedzi ktora juz jest true to nie idziemy dalej szukac bo mamy pewnosc ze tak jest
	//dijkstra jesli dociera do krawedzi ktora juz ma true w dojscu do tej partycji zatrzymuje dzialanie i zwraca array dojscia do tej krawedzi nie dalej bo dalej nie trzeba bo juz raz zostalo to obliczone


}


ArcFlagsCreator::~ArcFlagsCreator()
{
}
