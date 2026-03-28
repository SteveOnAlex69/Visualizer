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
	void add_node(Node v);
	void add_edge(int u, int v);
	std::vector<Node> get_node_list();
	std::vector<std::pair<int, int>> get_edges_val(); // get all of the edges by value
	std::vector<std::pair<int, int>> get_edges_idx(); // get all of the edges by index
private:
	std::set<Node> nodes;
	std::vector<std::pair<int, int>> edges;
};

#endif