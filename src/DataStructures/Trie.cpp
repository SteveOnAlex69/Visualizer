#include <DataStructures/Trie.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <utility>

TrieNode::TrieNode() {
    cnt = sum = 0;
    for (int i = 0; i < ALPHA; ++i) child[i] = nullptr;
}

Trie::Trie() {
    root = new TrieNode();
    root->cnt = root->sum = 1;
}

void Trie::insert(std::string s) {
    TrieNode* cur = root;
    for (char c : s) {
        cur->sum++;
        if (cur->child[c - '0'] == nullptr)
            cur->child[c - '0'] = new TrieNode();
        cur = cur->child[c - '0'];
    }
    cur->sum++;
    cur->cnt++;
}

bool Trie::erase(std::string s) { // obviously s has to already be in the trie
    return try_remove(root, 0, s);
}

bool Trie::try_remove(TrieNode*& root, int i, std::string& s) {
    if (root == nullptr) return false;
    bool check = true;
    if (i < s.size()) {
        check = try_remove(root->child[s[i] - '0'], i + 1, s);
    }
    else {
        if (root->cnt == 0) return false;
        root->cnt--; 
    }

    if (check) {
        root->sum--;
        if (root->sum == 0) {
            delete root;
            root = nullptr;
        }
    }
    return check;
}

std::vector<void*> Trie::search(std::string s) {
    TrieNode* tmp = root;
    std::vector<void*> ans;
    for (char c : s) {
        ans.push_back(tmp);
        if (tmp == nullptr) return ans;
        tmp = tmp->child[c - '0'];
    }
    ans.push_back(tmp);
    if (tmp -> cnt == 0) ans.push_back(nullptr);
    return ans;
}

bool Trie::exist(std::string s) {
    return search(s).back() == nullptr;
}

void Trie::clear() {
    internal_clear(root);

    root = new TrieNode();
    root->cnt = root->sum = 1;
}

void Trie::internal_clear(TrieNode* root) {
    if (root == nullptr) return;
    for (int i = 0; i < ALPHA; ++i) internal_clear(root->child[i]);
    delete(root);
}