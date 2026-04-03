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
	std::string val;
	LLNode(std::string v = "");
};

class LinkedList {
public:
	LLNode* head;
	LinkedList();
	void insert(std::string value);
	bool erase(std::string value); // return whether deleted successfully
	LLNode* search(std::string value);
	bool exist(std::string value);

	std::vector<LLNode*> get_array();

	void clear();
private:

};



#endif