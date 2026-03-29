#include <Trie.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <utility>

TrieNode::TrieNode() {
    cnt = 0;
    for (int i = 0; i < 26; ++i) child[i] = nullptr;
}

Trie::Trie() {
    root = new TrieNode();
    root->cnt++;
}

void Trie::add(std::string s) {
    TrieNode* cur = root;
    for (char c : s) {
        cur->cnt++;
        if (cur->child[c - 'a'] == nullptr)
            cur->child[c - 'a'] = new TrieNode();
        cur = cur->child[c - 'a'];
    }
    cur->cnt++;
}

void Trie::remove(std::string s) { // obviously s has to already be in the trie
    try_remove(root, 0, s);
}

void Trie::try_remove(TrieNode*& root, int i, std::string& s) {
    if (i < s.size()) {
        try_remove(root->child[s[i] - 'a'], i + 1, s);
    }
    root->cnt--;
    if (root->cnt == 0) {
        delete root;
        root = nullptr;
    }
}

TrieNode* Trie::find(std::string s) {
    TrieNode* ans = root;
    for (char c : s) {
        if (ans->child[c - 'a'] == nullptr)
            return nullptr;
        ans = ans->child[c - 'a'];
    }
    return ans;
}

bool Trie::exist(std::string s) {
    return find(s) == nullptr;
}