#include "GraphCreator.h"
#include "HeaderInclude.h"

GraphCreator::GraphCreator() {
	graph = createGraph();
}

GraphCreator::~GraphCreator() {
}

ResultSet* GraphCreator::executeMySqlQuery(string sql) {
	Statement* statement = MySqlConnection::getMySqlConnection().con->createStatement();

	return statement->executeQuery(sql);
}

ResultSet* GraphCreator::getNodes() {
	return executeMySqlQuery("Select * from node");
}

ResultSet* GraphCreator::getEdges() {
	return executeMySqlQuery("Select * from edge");
}

void GraphCreator::setNodes(Graph *graph) {
	ResultSet *nodes = getNodes();
	int nodesCount = 0;

	while (nodes->next()) {
		graph->addNode(GraphNode(nodes->getInt("id"), nodes->getInt("partitionNumber")));
		nodesCount++;
	}

	cout << "Added " << nodesCount << " nodes" << endl;
}

void GraphCreator::setEdges(Graph *graph) {
	ResultSet *edges = getEdges();
	int edgesCount = 0;

	while (edges->next()) {
		GraphNode *nodeFrom = graph->getNode(edges->getInt("fromId"));
		GraphNode *nodeTo = graph->getNode(edges->getInt("toId"));
		graph->addEdgeToNodes(GraphEdge(edges->getInt("id"), (short int)edges->getInt("directionCol"), nodeFrom, nodeTo, edges->getDouble("length")));
		edgesCount++;
	}

	cout << "Added " << edgesCount << " edges" << endl;
}

Graph* GraphCreator::createGraph() {
	Graph graph = Graph();

	setNodes(&graph); 
	setEdges(&graph);
	return &graph;
}

Graph* GraphCreator::getGraph() {
	return graph;
}