#ifndef TRIE_HPP
#define TRIE_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <utility>

const int ALPHA = 10;
struct TrieNode {
    int cnt;
    TrieNode* child[ALPHA];
    TrieNode();
    bool no_bitch();
};

class Trie {
public:
    TrieNode* root;
    Trie();
    int insert(std::string s);
    int erase(std::string s);
    std::vector<void*> search(std::string s);
    bool exist(std::string s);
    void clear();
private:
    void internal_clear(TrieNode* root);
};



#endif