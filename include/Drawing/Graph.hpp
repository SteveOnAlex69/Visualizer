#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <utility>
#include <Drawing/Node.hpp>

struct Edge {
	Node* first, *second;
	std::string val;
	Edge(Node *u, Node *v, std::string s = "");
};

class Graph {
public:
	Graph();
	~Graph();
	Node* add_node(Node *v);
	void add_edge(Node *u, Node *v, std::string s = "");
	void add_edge(std::string u, std::string v, std::string s = "");
	std::vector<Node*> get_node_list();
	std::vector<Edge> get_edges_idx(); // get all of the edges by pointer
private:
	std::vector<Node*> nodes;
	std::vector<Edge> edges;
	Node* find_node(std::string u);
};

#endif