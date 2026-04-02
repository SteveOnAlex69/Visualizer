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
	int hash_function(std::string x);
	void insert(std::string x);
	bool erase(std::string x); // return whether deletion was successful
	bool exist(std::string x);
	LLNode* locate(std::string x);
private:
	int n;
};

class HashMapLinearProbing {
public:
	int get_size();
	std::vector<std::string> slots;
	HashMapLinearProbing(int n = 0); // its preferable that n = prime
	int hash_function(std::string x);
	void insert(std::string x);
	bool erase(std::string x); // return whether deletion was successful
	bool exist(std::string x);
	int locate(std::string x);
private:
	int n;
};



#endif