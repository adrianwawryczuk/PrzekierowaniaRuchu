#pragma once

#include "MySqlConnection.h"
#include "Graph.h"

using namespace sql;

class GraphCreator
{
public:
	static Graph* getGraph();
	static ResultSet* getNodes();
	static ResultSet* getEdges();
	static Graph* createGraph();

private:
	static ResultSet* executeMySqlQuery(string sql);
	static void setNodes(Graph* graph);
	static void setEdges(Graph* graph);
};
