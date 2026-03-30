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
    int cnt;
    TrieNode* child[26];
    TrieNode();
};

class Trie {
public:
    TrieNode* root;
    Trie();
    void add(std::string s);
    void remove(std::string s);
    TrieNode* find(std::string s);
    bool exist(std::string s);
private:
    void try_remove(TrieNode*& root, int i, std::string& s);
};



#endif