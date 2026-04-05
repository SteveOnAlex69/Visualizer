#include <Drawing/Node.hpp>
#include <Drawing/Graph.hpp>
#include <iostream>
#include <vector>
#include <utility>

Edge::Edge(unsigned long long x, unsigned long long y, std::string s, float o) {
	first = x;
	second = y;
	val = s;
	opacity = o;
}


Graph::Graph(bool clear_memory) {
	will_clear_memory = clear_memory;
}

Node Graph::add_node(Node v) {
	nodes.push_back(v);
	return v;
}
void Graph::add_edge(unsigned long long u, unsigned long long v, std::string s, float opacity) {
	edges.push_back(Edge(u, v, s, opacity));
}
void Graph::add_edge(Node u, Node v, std::string s, float opacity) {
	edges.push_back(Edge(u.get_hash_val(), v.get_hash_val(), s, opacity));
}
std::vector<Node> Graph::get_node_list() {
	return nodes;
}

Node Graph::find_node(std::string u) {
	for (Node i : nodes) {
		if (i.get_val() == u) {
			return i;
		}
	}
	return Node();
}
Node Graph::find_node(unsigned long long u) {
	for (Node i : nodes) {
		if (i.get_hash_val() == u) {
			return i;
		}
	}
	return Node();
}

void Graph::add_edge(std::string u, std::string v, std::string s, float opacity) {
	Node m1 = find_node(u), m2 = find_node(v);
	if (m1.get_val() == "null" || m2.get_val() == "null") return;
	add_edge(m1, m2, s, opacity);
}

std::vector<Edge> Graph::get_edges_idx() {
	return edges;
}