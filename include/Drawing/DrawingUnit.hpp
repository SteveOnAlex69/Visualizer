#ifndef DRAWINGUNIT_HPP
#define DRAWINGUNIT_HPP

#include <SFML/Graphics.hpp>
#include <Helper.hpp>
#include <Drawing/Node.hpp>
#include <Drawing/Graph.hpp>
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

	void draw_node(Node i);
	void draw_edge(Node u, Node v, std::string val, float opacity, sf::Color color);
	void draw_graph(Graph& graph);
 // draw between two graph
private:
	sf::RenderWindow* appwindow;
	sf::Font font;
};


#endif