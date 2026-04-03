#ifndef GENERAL_HPP
#define GENERAL_HPP
#include <SFML/Graphics.hpp>
#include <DataStructures/LinkedList.hpp>
#include <DataStructures/Hashmap.hpp>
#include <DataStructures/AVL.hpp>
#include <DataStructures/Trie.hpp>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <utility>

enum DS {
	LINKED_LIST = 0,
	HASHMAP_CHAIN = 1, 
	BST_TREE = 2,
	AVL_TREE = 3,
	TRIE = 4
};

class GeneralData {
public:
	GeneralData();
	void reset_current();

	void* get_current_structure();
	DS get_current_type();
	void change_data_structure(DS st);
	void next_data_structure();
	void previous_data_structure();

	void insert(std::string s);
	bool erase(std::string s);
	void* search(std::string s);
	
private:
	DS selected_ds;
	LinkedList li;
	HashMapChaining mp_chain;
	AVL bst_tree, avl_tree;
	Trie tri;
};


#endif