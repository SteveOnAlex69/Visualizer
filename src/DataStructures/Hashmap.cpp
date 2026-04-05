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
LLNode* HashMapChaining::search(std::string x) {
	return buckets[hash_function(x)].search(x);
}
void HashMapChaining::clear() {
	for (int i = 0; i < n; ++i)
		buckets[i].clear();
}
