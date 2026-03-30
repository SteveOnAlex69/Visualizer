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

int HashMapChaining::hash_function(int x) {
	x %= n;
	if (x < 0) x += n;
	return x;
}
void HashMapChaining::insert(int x) {
	buckets[hash_function(x)].insert(x);
}
bool HashMapChaining::erase(int x) {
	return buckets[hash_function(x)].erase(x);
}
bool HashMapChaining::exist(int x) {
	return buckets[hash_function(x)].exist(x);
}
LLNode* HashMapChaining::locate(int x) {
	return buckets[hash_function(x)].locate(x);
}


int HashMapLinearProbing::get_size() {
	return n;
}

HashMapLinearProbing::HashMapLinearProbing(int _n) {
	n = _n;
	slots.resize(n, -1);
}

int HashMapLinearProbing::hash_function(int x) {
	x %= n;
	if (x < 0) x += n;
	return x;
}
void HashMapLinearProbing::insert(int x) {
	int idx = hash_function(x);
	while (slots[idx] != -1) {
		idx++;
		if (idx == n) idx -= n;
	}
	slots[idx] = x;
}
bool HashMapLinearProbing::erase(int x) {
	int idx = locate(x);
	if (idx != -1) {
		slots[idx] = -1;
		return true;
	}
	else return false;
}
bool HashMapLinearProbing::exist(int x) {
	return locate(x) != -1;
}
int HashMapLinearProbing::locate(int x) {
	int idx = hash_function(x);
	for (int it = 0; it < std::min(n, 100); ++it) {
		if (slots[idx] == x) return idx;
		idx++;
		if (idx == n) idx -= n;
	}
	return -1;

}
