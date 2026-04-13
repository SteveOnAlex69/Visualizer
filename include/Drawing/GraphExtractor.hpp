#ifndef GRAPHEXTRACTOR_HPP
#define GRAPHEXTRACTOR_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <utility>
#include <Drawing/Node.hpp>
#include <Drawing/Graph.hpp>
#include <DataStructures/LinkedList.hpp>
#include <DataStructures/Hashmap.hpp>
#include <DataStructures/Trie.hpp>
#include <DataStructures/AVL.hpp>
#include <DataStructures/Kruskal.hpp>
#include <DataStructures/Dijkstra.hpp>
#include <DataStructures/General.hpp>
#include <Helper.hpp>

namespace GraphExtractor {
	Graph get_linked_list_graph(LinkedList* linked_list, sf::Vector2f ROOT, std::vector<void*> highlighted);
	Graph get_hash_map_graph(HashMapChaining* hash_map, sf::Vector2f ROOT, std::vector<void*> highlighted);
	Graph get_BST_graph(AVL* bst, sf::Vector2f ROOT, std::vector<void*> highlighted);
	Graph get_trie_graph(Trie* tri, sf::Vector2f ROOT, std::vector<void*> highlighted);

	Graph get_kruskal_graph(Kruskal* kurst, sf::Vector2f ROOT, int it = -1);
	Graph get_dijkstra_graph(Dijkstra* dik, sf::Vector2f ROOT,
		std::vector<int> highlight1, std::vector<int> highlight2,
		std::vector<std::pair<int, int>> edges1, std::vector<std::pair<int, int>> edges2);

	Graph get_graph(GeneralData& ds, void* highlighted = nullptr, int cnt = 1);
}

#endif