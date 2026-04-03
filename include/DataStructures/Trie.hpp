#ifndef TRIE_HPP
#define TRIE_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <utility>

const int ALPHA = 10;
struct TrieNode {
    int cnt, sum;
    TrieNode* child[ALPHA];
    TrieNode();
};

class Trie {
public:
    TrieNode* root;
    Trie();
    void insert(std::string s);
    bool erase(std::string s);
    TrieNode* search(std::string s);
    bool exist(std::string s);
    void clear();
private:
    bool try_remove(TrieNode*& root, int i, std::string& s);
    void internal_clear(TrieNode* root);
};



#endif