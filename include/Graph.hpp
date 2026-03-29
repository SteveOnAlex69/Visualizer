#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <utility>
#include <Node.hpp>

class Graph {
public:
	Graph();
	~Graph();
	Node* add_node(Node *v);
	void add_edge(Node *u, Node *v);
	void add_edge(std::string u, std::string v);
	std::vector<Node*> get_node_list();
	std::vector<std::pair<std::string, std::string>> get_edges_val(); // get all of the edges by value
	std::vector<std::pair<Node*, Node*>> get_edges_idx(); // get all of the edges by pointer
private:
	std::vector<Node*> nodes;
	std::vector<std::pair<Node*, Node*>> edges;
	Node* find_node(std::string u);
};

#endif