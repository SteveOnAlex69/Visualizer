#include <BST.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <utility>

BSTNode::BSTNode(int x) { val = x; childL = childR = nullptr; }

BST::BST() {
    root = nullptr;
}

void BST::insert(int x) {
    insert(root, x);
}

void BST::insert(BSTNode*& root, int x) {
    if (root == nullptr) {
        root = new BSTNode(x);
        return;
    }
    if (x < root->val) insert(root->childL, x);
    else insert(root->childR, x);
}

void BST::traverse() {
    std::vector<int> ans;
    traverse(root, ans);
}

void BST::traverse(BSTNode* root, std::vector<int>& ans) {
    if (root == nullptr) return;
    traverse(root->childL, ans);
    ans.push_back(root->val);
    traverse(root->childR, ans);
}

BSTNode* BST::locate(int x) {
    return locate(root, x);
}

BSTNode* BST::locate(BSTNode* root, int x) {
    if (root == nullptr) return nullptr;
    if (root->val == x) return root;
    if (x < root->val) return locate(root->childL, x);
    else return locate(root->childR, x);
}

bool BST::exist(int x) {
    return locate(x) != nullptr;
}

bool BST::erase(int x) {
    return erase(root, x);
}

bool BST::erase(BSTNode*& root, int x) {
    if (root == nullptr) return false;
    if (x == root->val) { // delete this shit
        if (root->childR) {
            int val = delete_left_most(root->childR);
            root->val = val;
        }
        else {
            BSTNode* tmp = root;
            root = root->childL;
            delete tmp;
        }
        return true;
    }
    if (x < root->val) return erase(root->childL, x);
    else return erase(root->childR, x);
}

int BST::delete_left_most(BSTNode*& root) {
    if (root->childL) return delete_left_most(root->childL);
    else {
        BSTNode* tmp = root->childR;
        int ans = root->val;
        delete root;
        root = tmp;
        return ans;
    }
}