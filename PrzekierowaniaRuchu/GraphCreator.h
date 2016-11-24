#pragma once

#include "MySqlConnection.h"
#include "Graph.h"

using namespace sql;

class GraphCreator
{
public:
	GraphCreator();
	~GraphCreator();

	Graph *getGraph();
	ResultSet* getNodes();
	ResultSet* getEdges();

private:
	Graph *graph;
	Graph* createGraph();
	ResultSet* executeMySqlQuery(string sql);
	void setNodes(Graph *graph);
	void setEdges(Graph *graph);
};

