#include <Node.hpp>
#include <Graph.hpp>
#include <iostream>
#include <vector>
#include <utility>

Graph::Graph() {
}


void Graph::add_node(Node v) {
	nodes.insert(v);
}
void Graph::add_edge(int u, int v) {
	edges.push_back(std::make_pair(u, v));
}
std::vector<Node> Graph::get_node_list() {
	return std::vector(nodes.begin(), nodes.end());
}
std::vector<std::pair<int, int>> Graph::get_edges_val() {
	return edges;
}
std::vector<std::pair<int, int>> Graph::get_edges_idx() {
	std::vector<std::pair<int, int>> ans;
	for (auto i : edges) {
		int idx1 = -1, idx2 = -1;
		int it = 0;
		for (auto j : nodes) {
			if (j.get_val() == i.first) {
				idx1 = it;
			}
			if (j.get_val() == i.second) {
				idx2 = it;
			}
			it++;
		}
		if (idx1 != -1 && idx2 != -1) {
			ans.push_back(std::make_pair(idx1, idx2));
		}
	}
	return ans;
}