#include <DataStructures/LinkedList.hpp>
#include <iostream>
#include <vector>
#include <utility>

LLNode::LLNode(std::string v) {
	val = v;
	nxt = nullptr;
}

LinkedList::LinkedList() {
	head = new LLNode("");
}


void LinkedList::insert(std::string value) {
	LLNode* cur = new LLNode(value);
	cur->nxt = head->nxt;
	head->nxt = cur;
}

bool LinkedList::erase(std::string value) {
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

std::vector<void*> LinkedList::search(std::string value) {
	LLNode* tmp = head;
	std::vector<void*> ans;
	while (tmp->nxt) {
		tmp = tmp->nxt;
		ans.push_back(tmp);
		if (tmp->val == value) 
			return ans;
	}
	ans.push_back(nullptr);
	return ans;
}
bool LinkedList::exist(std::string value) {
	return (search(value).back() != nullptr);
}

std::vector<LLNode*> LinkedList::get_array() {
	std::vector<LLNode*> ans;
	LLNode* tmp = head;
	ans.push_back(head);
	while (tmp->nxt) {
		tmp = tmp->nxt;
		ans.push_back(tmp);
	}
	return ans;
}

void LinkedList::clear() {
	while (head->nxt) {
		erase(head->nxt->val);
	}
}