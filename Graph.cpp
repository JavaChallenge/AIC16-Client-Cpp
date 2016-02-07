#include "Graph.h"

Graph::Graph(std::vector<Node*> nodes)
{
	this->nodes = nodes;
}

std::vector<Node*> Graph::getNodes()
{
	return this->nodes;
}

Node * Graph::getNode(int index)
{
	return nodes[index];
}
