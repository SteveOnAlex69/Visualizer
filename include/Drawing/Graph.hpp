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
	unsigned long long first, second;
	std::string val;
	float opacity;
	Edge(unsigned long long u, unsigned long long v, std::string s = "", float o = 1);
};

class Graph {
public:
	Graph(bool memory_clear = false);
	Node add_node(Node v);
	void add_edge(unsigned long long u, unsigned long long v, std::string s = "", float opacity = 1);
	void add_edge(Node u, Node v, std::string s = "", float opacity = 1);
	void add_edge(std::string u, std::string v, std::string s = "", float opacity = 1);
	std::vector<Node> get_node_list();
	std::vector<Edge> get_edges_idx(); // get all of the edges by pointer

	Node Graph::find_node(unsigned long long u);
private:
	std::vector<Node> nodes;
	std::vector<Edge> edges;
	Node find_node(std::string u);
	bool will_clear_memory;
};

#endif