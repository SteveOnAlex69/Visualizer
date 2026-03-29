#include <Node.hpp>
#include <Graph.hpp>
#include <iostream>
#include <vector>
#include <utility>

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
void Graph::add_edge(Node* u, Node* v) {
	edges.push_back(std::make_pair(u, v));
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

void Graph::add_edge(std::string u, std::string v) {
	Node* m1 = find_node(u), *m2 = find_node(v);
	if (m1 == nullptr || m2 == nullptr) return;
	add_edge(m1, m2);
}

std::vector<std::pair<Node*, Node*>> Graph::get_edges_idx() {
	return edges;
}

std::vector<std::pair<std::string, std::string>> Graph::get_edges_val() {
	std::vector<std::pair<std::string, std::string>> ans;
	for(auto i: edges)
		ans.push_back(std::make_pair(i.first->get_val(), i.second->get_val()));
	return ans;
}