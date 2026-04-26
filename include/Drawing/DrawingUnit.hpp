#ifndef DRAWINGUNIT_HPP
#define DRAWINGUNIT_HPP

#include <SFML/Graphics.hpp>
#include <Helper.hpp>
#include <Drawing/Node.hpp>
#include <Drawing/Graph.hpp>
#include <Drawing/Pseudocode.hpp>
#include <Drawing/VisualizerState.hpp>
#include <DataStructures/LinkedList.hpp>
#include <DataStructures/Hashmap.hpp>
#include <DataStructures/Trie.hpp>
#include <DataStructures/AVL.hpp>
#include <DataStructures/Kruskal.hpp>
#include <DataStructures/Dijkstra.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
#include <concepts>
#include <math.h>

class DrawingUnit {
public:
	DrawingUnit();
	DrawingUnit(sf::RenderWindow *window, sf::Font f);

	void draw_node(Node i, bool flag = false);
	void draw_edge(Node u, Node v, std::string val, float opacity, sf::Color color);
	void draw_viz_state(VisualizerState& viz_lu, bool flag);
	void draw_graph(Graph& graph, bool flag);
	void draw_pseudo_code(Pseudocode& sudo_code);

	void shift_canvas(sf::Vector2f v);
	void scale_canvas(sf::Vector2f mouse_pos, int delta);
private:
	sf::RenderWindow* appwindow;
	sf::Font font;
	
	float scaling = 1;
	sf::Vector2f root = sf::Vector2f(0, 0);
};


#endif