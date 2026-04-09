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
	void draw_graph(Graph& graph);
	void draw_edge(Node u, Node v, std::string val, float opacity = 1);

	Graph get_linked_list_graph(LinkedList* linked_list, sf::Vector2f ROOT, LLNode* highlighted_node = nullptr);
	Graph get_hash_map_graph(HashMapChaining* hash_map, sf::Vector2f ROOT, LLNode* highlighted_node = nullptr);
	Graph get_BST_graph(AVL* bst, sf::Vector2f ROOT, AVLNode* highlighted_node = nullptr);
	Graph get_trie_graph(Trie* tri, sf::Vector2f ROOT, TrieNode* highlighted_node = nullptr);

	Graph get_kruskal_graph(Kruskal* kurst, sf::Vector2f ROOT);
	Graph get_dijkstra_graph(Dijkstra* dik, sf::Vector2f ROOT);

	void draw_graph_stage1(Graph& graph1, Graph& graph2, float epoch);
	void draw_graph_stage2(Graph& graph1, Graph& graph2, float epoch);
	void draw_graph_stage3(Graph& graph1, Graph& graph2, float epoch);
	void draw_graph(Graph& graph1, Graph& graph2, float epoch); // draw between two graph
private:
	sf::RenderWindow* appwindow;
	sf::Font font;


};


#endif