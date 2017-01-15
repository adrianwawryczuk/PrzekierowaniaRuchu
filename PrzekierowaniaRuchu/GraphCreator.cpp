#include "GraphCreator.h"
#include "HeaderInclude.h"

ResultSet* GraphCreator::executeMySqlQuery(string sql)
{
	auto* statement = MySqlConnection::getMySqlConnection().con->createStatement();

	return statement->executeQuery(sql);
}

ResultSet* GraphCreator::getNodes()
{
	return executeMySqlQuery("Select * from node");
}

ResultSet* GraphCreator::getEdges()
{
	return executeMySqlQuery("Select * from edge");
}

void GraphCreator::setNodes(Graph* graph)
{
	auto* nodes = getNodes();
	auto nodesCount = 0;

	while (nodes->next())
	{
		graph->addNode(GraphNode(nodes->getInt("id"), nodes->getInt("partitionNumber")));
		nodesCount++;
	}

	cout << "Added " << nodesCount << " nodes" << endl;
}

void GraphCreator::setEdges(Graph* graph)
{
	auto edges = getEdges();
	auto edgesCount = 0;
	GraphNode* nodeFrom;
	GraphNode* nodeTo;
	while (edges->next())
	{
		nodeFrom = graph->getNode(edges->getInt("fromId"));
		nodeTo = graph->getNode(edges->getInt("toId"));

		graph->addEdgeToNodes(
			GraphEdge(
				edges->getInt("id"), 
					static_cast<short int>(edges->getInt("directionCol")), 
						nodeFrom, 
							nodeTo,
								static_cast<float>(edges->getDouble("length")), 
									edges->getString("arcFlags")));
		
		edgesCount++;
	}

	cout << "Added " << edgesCount << " edges" << endl;
}

Graph* GraphCreator::createGraph()
{
	setNodes(Graph::getGraph());
	setEdges(Graph::getGraph());
	return Graph::getGraph();
}

Graph* GraphCreator::getGraph()
{
	return Graph::getGraph();
}
