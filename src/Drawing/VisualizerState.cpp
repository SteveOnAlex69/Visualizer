#include <Drawing/VisualizerState.hpp>

VisualizerState::VisualizerState(Graph g, Pseudocode ps) {
	graph = g;
	sudo_code = ps;
}

Graph VisualizerState::get_graph() {
	return graph;
}

Pseudocode VisualizerState::get_pseudo_code() {
	return sudo_code;
}