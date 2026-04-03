#include <DataStructures/AVL.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <utility>


AVLNode::AVLNode(int x) { depth = 1; val = x; childL = childR = nullptr; }

int AVLNode::left_child_depth() {
    if (childL) return childL->depth;
    return 0;
}

int AVLNode::right_child_depth() {
    if (childR) return childR->depth;
    return 0;
}


AVL::AVL(bool is_self_balanced) {
    root = nullptr;
    is_avl = is_self_balanced;
}

void AVL::calculate_depth(AVLNode* x) {
    if (x == nullptr) return;
    x->depth = std::max(x->left_child_depth(), x->right_child_depth()) + 1;
}

int AVL::unbalanced(AVLNode* x) {
    calculate_depth(x);
    int diff = (x->left_child_depth()) - (x->right_child_depth());
    if (diff >= 2) return -1;
    if (diff <= -2) return 1;
    return 0;
}

void AVL::insert(int x) {
    insert(root, x);
}

void AVL::rotate_left(AVLNode*& root) {
    AVLNode* tmp = root->childL;
    root->childL = root->childL->childR;
    tmp->childR = root;
    calculate_depth(root);
    root = tmp;
    calculate_depth(root);
}
void AVL::rotate_right(AVLNode*& root) {
    AVLNode* tmp = root->childR;
    root->childR = root->childR->childL;
    tmp->childL = root;
    calculate_depth(root);
    root = tmp;
    calculate_depth(root);
}


void AVL::correct(AVLNode*& root) {
    if (is_avl == false) return;
    if (unbalanced(root) == -1) {
        rotate_left(root);
        if (unbalanced(root) == 1) {
            rotate_left(root->childR);
            calculate_depth(root);
            rotate_right(root);
        }
    }
    else if (unbalanced(root) == 1) {
        rotate_right(root);
        if (unbalanced(root) == -1) {
            rotate_right(root->childL);
            calculate_depth(root);
            rotate_left(root);
        }
    }
}

void AVL::insert(AVLNode*& root, int x) {
    if (root == nullptr) {
        root = new AVLNode(x);
        return;
    }
    if (x < root->val) insert(root->childL, x);
    else insert(root->childR, x);

    correct(root);
    calculate_depth(root);
}

void AVL::traverse() {
    if (root) {
        std::vector<int> ans;
        traverse(root, ans);
    }
}

void AVL::traverse(AVLNode* root, std::vector<int>& ans) {
    if (root->childL) {
        traverse(root->childL, ans);
    }

    ans.push_back(root->val);

    if (root->childR) {
        traverse(root->childR, ans);
    }
}

AVLNode* AVL::search(int x) {
    return locate(root, x);
}

AVLNode* AVL::locate(AVLNode* root, int x) {
    if (root == nullptr) return nullptr;
    if (root->val == x) return root;
    if (x < root->val) return locate(root->childL, x);
    else return locate(root->childR, x);
}

bool AVL::exist(int x) {
    return search(x) != nullptr;
}


bool AVL::erase(int x) {
    return erase(root, x);
}

bool AVL::erase(AVLNode*& root, int x) {
    if (root == nullptr) return false;
    if (x == root->val) { // delete this shit
        if (root->childR) {
            int val = delete_left_most(root->childR);
            root->val = val;
        }
        else {
            AVLNode* tmp = root;
            root = root->childL;
            delete tmp;
        }
        correct(root);
        return true;
    }
    bool check = false;
    if (x < root->val) check = erase(root->childL, x);
    else check = erase(root->childR, x);
    correct(root);
    return check;
}

int AVL::delete_left_most(AVLNode*& root) {
    if (root->childL) {
        int ans = delete_left_most(root->childL);
        correct(root);
        return ans;
    }
    else {
        AVLNode* tmp = root;
        root = root->childR;
        int ans = tmp->val;
        delete tmp;
        return ans;
    }
}


void AVL::clear() {
    internal_clear(root);
}

void AVL::internal_clear(AVLNode* root) {
    if (root == nullptr) return;
    internal_clear(root->childL);
    internal_clear(root->childR);
    delete root;
}


// for debugging purposes
bool AVL::check_correct_depth() {
    return check_correct_depth(root);
}

bool AVL::check_correct_depth(AVLNode* root) {
    if (root == nullptr) return true;
    int cur = root->depth;
    calculate_depth(root);
    if (root->depth != cur) return false;
    return check_correct_depth(root->childL) && check_correct_depth(root->childR);
}