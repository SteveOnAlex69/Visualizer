#include <LinkedList.hpp>
#include <iostream>
#include <vector>
#include <utility>

LLNode::LLNode(int v) {
	val = v;
	nxt = nullptr;
}

LinkedList::LinkedList() {
	head = new LLNode(0);
}


void LinkedList::insert(int value) {
	LLNode* cur = new LLNode(value);
	cur->nxt = head->nxt;
	head->nxt = cur;
}

bool LinkedList::erase(int value) { 
	LLNode* tmp = head;
	while (tmp->nxt) {
		if (tmp->nxt->val == value) {
			LLNode* vcl = tmp->nxt;
			tmp->nxt = tmp->nxt->nxt;
			delete vcl;
			return true;
		}
		tmp = tmp->nxt;
	}
	return false;
}
LLNode* LinkedList::locate(int value) {
	LLNode* tmp = head;
	while (tmp->nxt) {
		tmp = tmp->nxt;
		if (tmp->val == value) {
			return tmp;
		}
	}
	return nullptr;
}
bool LinkedList::exist(int value) {
	return (locate(value) != nullptr);
}

std::vector<int> LinkedList::get_array() {
	std::vector<int> ans;
	ans.push_back(0);
	LLNode* tmp = head;
	while (tmp->nxt) {
		tmp = tmp->nxt;
		ans.push_back(tmp->val);
	}
	return ans;
}
