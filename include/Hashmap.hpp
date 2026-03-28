#ifndef HASHMAP_HPP
#define HASHMAP_HPP
#include <SFML/Graphics.hpp>
#include <LinkedList.hpp>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <utility>

struct HashMapChaining {
	int n;
	std::vector<LinkedList> buckets;
	HashMapChaining(int n = 0); // its preferable that n = prime
	int hash_function(int x);
	void insert(int x);
	bool erase(int x); // return whether deletion was successful
	bool exist(int x);
	LLNode* locate(int x);
};

struct HashMapLinearProbing {
	int n;
	std::vector<int> slots;
	HashMapLinearProbing(int n = 0); // its preferable that n = prime
	int hash_function(int x);
	void insert(int x);
	bool erase(int x); // return whether deletion was successful
	bool exist(int x);
	int locate(int x);
};



#endif