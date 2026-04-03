#include <DataStructures/Hashmap.hpp>
#include <iostream>
#include <vector>
#include <utility>

int HashMapChaining::get_size() {
	return n;
}

HashMapChaining::HashMapChaining(int _n) {
	n = _n;
	buckets.resize(n);
}

int HashMapChaining::hash_function(std::string x) {
	int ans = 0;
	for (char c : x) {
		ans = (ans * 10 + (c - '0')) % n;
	}
	return ans;
}
void HashMapChaining::insert(std::string x) {
	buckets[hash_function(x)].insert(x);
}
bool HashMapChaining::erase(std::string x) {
	return buckets[hash_function(x)].erase(x);
}
bool HashMapChaining::exist(std::string x) {
	return buckets[hash_function(x)].exist(x);
}
LLNode* HashMapChaining::locate(std::string x) {
	return buckets[hash_function(x)].locate(x);
}
void HashMapChaining::clear() {
	for (int i = 0; i < n; ++i)
		buckets[i].clear();
}

int HashMapLinearProbing::get_size() {
	return n;
}

HashMapLinearProbing::HashMapLinearProbing(int _n) {
	n = _n;
	slots.resize(n, "");
}

int HashMapLinearProbing::hash_function(std::string x) {
	int ans = 0;
	for (char c : x) {
		ans = (ans * 10 + (c - '0')) % n;
	}
	return ans;
}

void HashMapLinearProbing::insert(std::string x) {
	int idx = hash_function(x);
	while (slots[idx] != "") {
		idx++;
		if (idx == n) idx -= n;
	}
	slots[idx] = x;
}
bool HashMapLinearProbing::erase(std::string x) {
	int idx = locate(x);
	if (idx != -1) {
		slots[idx] = -1;
		return true;
	}
	else return false;
}
bool HashMapLinearProbing::exist(std::string x) {
	return locate(x) != -1;
}
int HashMapLinearProbing::locate(std::string x) {
	int idx = hash_function(x);
	for (int it = 0; it < std::min(n, 100); ++it) {
		if (slots[idx] == x) return idx;
		idx++;
		if (idx == n) idx -= n;
	}
	return -1;
}


void HashMapLinearProbing::clear() {
	for (int i = 0; i < n; ++i)
		slots[i].clear();
}
