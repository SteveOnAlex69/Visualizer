#ifndef DRAWINGUNIT_HPP
#define DRAWINGUNIT_HPP

#include <SFML/Graphics.hpp>
#include <Helper.hpp>
#include <Drawing/Node.hpp>
#include <Drawing/Graph.hpp>
#include <DataStructures/LinkedList.hpp>
#include <DataStructures/Hashmap.hpp>
#include <DataStructures/Trie.hpp>
#include <DataStructures/BST.hpp>
#include <DataStructures/AVL.hpp>
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

	void draw_node(Node *i);
	void draw_graph(Graph& graph);

	void draw_linked_list(LinkedList& linked_list, sf::Vector2f ROOT, LLNode *highlighted_node = nullptr);
	void draw_hash_map(HashMapChaining& hash_map, sf::Vector2f ROOT);
	void draw_hash_map(HashMapLinearProbing& hash_map, sf::Vector2f ROOT);

	template <class Tree>
	void draw_BST(Tree& bst, sf::Vector2f ROOT);
	void draw_trie(Trie& tri, sf::Vector2f ROOT);

private:
	sf::RenderWindow* appwindow;
	sf::Font font;
};


#endif