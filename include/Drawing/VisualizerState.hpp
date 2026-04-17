#ifndef VISUALIZERSTATE_HPP
#define VISUALIZERSTATE_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <Helper.hpp>
#include <fstream>
#include <iostream>

#include <Drawing/Graph.hpp>
#include <Drawing/Pseudocode.hpp>

class VisualizerState {
public:
	VisualizerState(Graph graph, Pseudocode ps);

	Graph get_graph();
	Pseudocode get_pseudo_code();
private:
	Graph graph;
	Pseudocode sudo_code;
};

#endif