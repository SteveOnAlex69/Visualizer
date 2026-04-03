#ifndef TRIE_HPP
#define TRIE_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <utility>


struct TrieNode {
    int cnt, sum;
    TrieNode* child[26];
    TrieNode();
};

class Trie {
public:
    TrieNode* root;
    Trie();
    void add(std::string s);
    bool erase(std::string s);
    TrieNode* find(std::string s);
    bool exist(std::string s);

    void clear();

private:
    bool try_remove(TrieNode*& root, int i, std::string& s);
    void internal_clear(TrieNode* root);
};



#endif