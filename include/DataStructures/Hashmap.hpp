#ifndef HASHMAP_HPP
#define HASHMAP_HPP
#include <SFML/Graphics.hpp>
#include <DataStructures/LinkedList.hpp>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <utility>

class HashMapChaining {
public:
	int get_size();
	std::vector<LinkedList> buckets;
	HashMapChaining(int n = 0); // its preferable that n = prime
	int hash_function(int x);
	void insert(int x);
	bool erase(int x); // return whether deletion was successful
	bool exist(int x);
	LLNode* locate(int x);
private:
	int n;
};

class HashMapLinearProbing {
public:
	int get_size();
	std::vector<int> slots;
	HashMapLinearProbing(int n = 0); // its preferable that n = prime
	int hash_function(int x);
	void insert(int x);
	bool erase(int x); // return whether deletion was successful
	bool exist(int x);
	int locate(int x);
private:
	int n;
};



#endif