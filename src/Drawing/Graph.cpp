#include <Drawing/Node.hpp>
#include <Drawing/Graph.hpp>
#include <iostream>
#include <vector>
#include <utility>

Edge::Edge(Node* x, Node* y, std::string s) {
	first = x;
	second = y;
	val = s;
}


Graph::Graph() {

}

Graph::~Graph() {
	for (auto i : nodes) {
		delete i;
	}
}



Node* Graph::add_node(Node *v) {
	nodes.push_back(v);
	return v;
}
void Graph::add_edge(Node* u, Node* v, std::string s) {
	edges.push_back(Edge(u, v, s));
}
std::vector<Node*> Graph::get_node_list() {
	return nodes;
}

Node* Graph::find_node(std::string u) {
	for (Node* i : nodes) {
		if (i->get_val() == u) {
			return i;
		}
	}
	return nullptr;
}

void Graph::add_edge(std::string u, std::string v, std::string s) {
	Node* m1 = find_node(u), *m2 = find_node(v);
	if (m1 == nullptr || m2 == nullptr) return;
	add_edge(m1, m2, s);
}

std::vector<Edge> Graph::get_edges_idx() {
	return edges;
}