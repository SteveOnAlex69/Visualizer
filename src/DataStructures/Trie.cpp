#include <DataStructures/Trie.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <utility>

TrieNode::TrieNode() {
    cnt = 0;
    for (int i = 0; i < ALPHA; ++i) child[i] = nullptr;
}
bool TrieNode::no_bitch() {
    for (int i = 0; i < ALPHA; ++i) if (child[i]) return false;
    return true;
}

int TrieNode::get_leaf_count() {
    int ans = 1;
    int tot = 0;
    for (int i = 0; i < ALPHA; ++i) if (child[i]) tot += child[i]->get_leaf_count();
    return std::max(ans, tot);
}

Trie::Trie() {
    root = new TrieNode();
    root->cnt = 1;
}

int Trie::insert(std::string s) {
    TrieNode* cur = root;
    for (char c : s) {
        if (cur->child[c - '0'] == nullptr) {
            cur->child[c - '0'] = new TrieNode();
            return 2;
        }
        cur = cur->child[c - '0'];
    }
    cur->cnt++;
    return 1;
}

int Trie::erase(std::string s) { // obviously s has to already be in the trie
    TrieNode* cur = root, *pre = root;
    for (char c : s) {
        pre = cur;
        cur = cur->child[c - '0'];
        if (cur == nullptr) return 0;
        if (cur->no_bitch() && cur->cnt == 0) {
            pre->child[c - '0'] = nullptr;
            delete cur;
            return 2;
        }
    }
    if (cur != nullptr && cur->cnt) {
        cur->cnt--;
        if (cur->cnt == 0) {
            pre->child[s.back() - '0'] = nullptr;
            delete cur;
        }
        return 1;
    }
    return 0;
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
    if (tmp != nullptr && tmp -> cnt == 0) ans.push_back(nullptr);
    return ans;
}

bool Trie::exist(std::string s) {
    return search(s).back() == nullptr;
}

void Trie::clear() {
    for (int i = 0; i < ALPHA; ++i) {
        internal_clear(root->child[i]);
        root->child[i] = nullptr;
    }
    root->cnt = 1;
}

void Trie::internal_clear(TrieNode* root) {
    if (root == nullptr) return;
    for (int i = 0; i < ALPHA; ++i) internal_clear(root->child[i]);
    delete(root);
}