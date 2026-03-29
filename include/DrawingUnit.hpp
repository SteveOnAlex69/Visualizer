#ifndef DRAWINGUNIT_HPP
#define DRAWINGUNIT_HPP

#include <SFML/Graphics.hpp>
#include <Helper.hpp>
#include <Node.hpp>
#include <Graph.hpp>
#include <LinkedList.hpp>
#include <Hashmap.hpp>
#include <Trie.hpp>
#include <BST.hpp>
#include <AVL.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
#include <concepts>
#include <math.h>

struct DrawingUnit {
	sf::RenderWindow *appwindow;
	sf::Font font;
	DrawingUnit();
	DrawingUnit(sf::RenderWindow *window, sf::Font f);

	void draw_node(Node *i);
	void draw_graph(Graph& graph);
	void draw_linked_list(LinkedList& linked_list, sf::Vector2f ROOT);
	void draw_hash_map(HashMapChaining& chenning, sf::Vector2f ROOT);

	template <class Tree>
	void draw_BST(Tree& bst, sf::Vector2f ROOT);

	void draw_trie(Trie& tri, sf::Vector2f ROOT);
};


#endif