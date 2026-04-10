#ifndef GENERAL_HPP
#define GENERAL_HPP
#include <SFML/Graphics.hpp>
#include <DataStructures/LinkedList.hpp>
#include <DataStructures/Hashmap.hpp>
#include <DataStructures/AVL.hpp>
#include <DataStructures/Trie.hpp>
#include <DataStructures/Dijkstra.hpp>
#include <DataStructures/Kruskal.hpp>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <utility>

const int TOTAL_DS_COUNT = 6;
enum DS {
	LINKED_LIST = 0,
	HASHMAP_CHAIN = 1,
	AVL_TREE = 2,
	TRIE = 3,
	KRUSKAL = 4,
	DIJKSTRA = 5
};

std::string get_ds_name(DS name);

class GeneralData {
public:
	GeneralData();
	void reset_current();

	void* get_current_structure();
	DS get_current_type();
	bool is_drawing_ds();
	void change_data_structure(DS st);
	void next_data_structure();
	void previous_data_structure();

	bool insert(std::string s);
	bool erase(std::string s);
	std::vector<void*> search(std::string s);

	void run();
	
private:
	DS selected_ds;
	LinkedList li;
	HashMapChaining mp_chain;
	AVL avl_tree;
	Trie tri;
	Dijkstra dijkstra;
	Kruskal kruskal;
};


#endif