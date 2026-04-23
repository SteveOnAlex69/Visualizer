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
    int get_leaf_count();
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
    int get_count(std::string s);

    void proper_insert(std::string s);
private:
    void internal_clear(TrieNode* root);
};



#endif