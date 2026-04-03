#ifndef GENERAL_HPP
#define GENERAL_HPP
#include <SFML/Graphics.hpp>
#include <DataStructures/LinkedList.hpp>
#include <DataStructures/Hashmap.hpp>
#include <DataStructures/BST.hpp>
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
	HASHMAP_LINEAR = 2,
	BST_TREE = 4,
	AVL_TREE = 5,
	TRIE = 6
};

class GeneralData {
public:

private:
	DS selected_ds;
	LinkedList li;
	HashMapChaining mp_chain;
	HashMapLinearProbing mp_linear;
	BST bst_tree;
	AVL avl_tree;
	Trie tri;
};


#endif