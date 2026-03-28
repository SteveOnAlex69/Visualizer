#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <utility>

struct LLNode {
	LLNode* nxt;
	int val;
	LLNode(int v = 0);
};

struct LinkedList {
	LLNode* head;
	LinkedList();
	void insert(int value);
	bool erase(int value); // return whether deleted successfully
	LLNode* locate(int value);
	bool exist(int value);

	std::vector<int> get_array();
};



#endif