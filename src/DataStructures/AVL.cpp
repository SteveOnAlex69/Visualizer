#include <DataStructures/AVL.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <utility>


AVLNode::AVLNode(int x) { depth = 1; val = x; childL = childR = nullptr; }


int AVLNode::get_tree_size() {
    int ans = 1;
    if (childL) ans += childL->get_tree_size();
    if (childR) ans += childR->get_tree_size();
    return ans;
}

int AVLNode::left_child_depth() {
    if (childL) return childL->depth;
    return 0;
}

int AVLNode::right_child_depth() {
    if (childR) return childR->depth;
    return 0;
}

int AVLNode::check_unbalanced() {
    return (abs(left_child_depth() - right_child_depth()) >= 2);
}

int AVLNode::get_min() {
    if (childL == nullptr) return val;
    return childL->get_min();
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


bool AVL::correct(AVLNode*& root) {
    if (root == nullptr) return false;
    if (is_avl == false) return false;
    if (unbalanced(root) == -1) {
        rotate_left(root);
        if (unbalanced(root) == 1) {
            rotate_left(root->childR);
            calculate_depth(root);
            rotate_right(root);
        }
        return true;
    }
    else if (unbalanced(root) == 1) {
        rotate_right(root);
        if (unbalanced(root) == -1) {
            rotate_right(root->childL);
            calculate_depth(root);
            rotate_left(root);
        }
        return true;
    }
    return false;
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

std::vector<void*> AVL::search_before_insert(int x) {
    std::vector<void*> ans;
    if (root == nullptr) return ans;
    AVLNode* tmp = root;

    while (tmp != nullptr) {
        ans.push_back(tmp);
        if (x < tmp->val) tmp = tmp->childL;
        else tmp = tmp->childR;
    }
    
    return ans;
}
std::vector<bool> AVL::search_before_insert_direction(int x) {
    std::vector<bool> ans;
    if (root == nullptr) return ans;
    AVLNode* tmp = root;
    while (tmp != nullptr) {
        if (x < tmp->val) {
            ans.push_back(0);
            tmp = tmp->childL;
        }
        else {
            ans.push_back(1);
            tmp = tmp->childR;
        }
    }

    return ans;
}

void AVL::insert(int x) {
    insert(root, x);
}
void AVL::insert(AVLNode*& root, int x) {
    if (root == nullptr) {
        root = new AVLNode(x);
        return;
    }
    if (x < root->val) insert(root->childL, x);
    else insert(root->childR, x);

    calculate_depth(root);
}


bool AVL::balance_the_tree() {
    bool check = false;
    while (balance_deepest_node()) check = true;
    return check;
}
bool AVL::balance_deepest_node() {
    return balance_the_tree(root);
}
bool AVL::balance_the_tree(AVLNode*& root) {
    if (root == nullptr) 
        return false;

    if (balance_the_tree(root->childL)) return true;
    if (balance_the_tree(root->childR)) return true;
    bool ans = correct(root);
    calculate_depth(root);
    return ans;
}



std::vector<void*> AVL::search(int x) {
    std::vector<void*> ans;
    AVLNode* tmp = root;

    while (true) {
        ans.push_back(tmp);
        if (tmp == nullptr || tmp->val == x) break;
        if (x < tmp->val) tmp = tmp->childL;
        else tmp = tmp->childR;
    }
    return ans;
}
std::vector<bool> AVL::search_direction(int x) {
    std::vector<bool> ans;
    AVLNode* tmp = root;

    while (true) {
        if (tmp == nullptr || tmp->val == x) break;
        ans.push_back(x > (tmp->val));
        if (x < tmp->val) tmp = tmp->childL;
        else tmp = tmp->childR;
    }
    return ans;
}


bool AVL::exist(int x) {
    return search(x).back() != nullptr;
}


bool AVL::erase(int x) {
    return erase(root, x);
}

bool AVL::erase(AVLNode*& root, int x) {
    if (root == nullptr) return false;
    if (x == root->val) { // delete this shit
        if (root->childR) {
            AVLNode* val = delete_left_most(root->childR);
            val->childL = root->childL;
            val->childR = root->childR;
            
            delete root;
            root = val;
            calculate_depth(root);
        }
        else {
            AVLNode* tmp = root;
            root = root->childL;
            delete tmp;
        }
        return true;
    }
    bool check = false;
    if (x < root->val) check = erase(root->childL, x);
    else check = erase(root->childR, x);

    calculate_depth(root);
    return check;
}

AVLNode* AVL::delete_left_most(AVLNode*& root) {
    if (root->childL) {
        AVLNode* ans = delete_left_most(root->childL);
        calculate_depth(root);
        return ans;
    }
    else {
        AVLNode* tmp = root;
        root = root->childR;
        calculate_depth(root);
        return tmp;
    }
}


void AVL::clear() {
    internal_clear(root);
    root = nullptr;
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
    bool ans = check_correct_depth(root->childL) && check_correct_depth(root->childR);
    calculate_depth(root);
    if (root->depth != cur) ans = false;
    return ans;
}


bool AVL::check_unbalanced() {
    return check_unbalanced(root);
}

bool AVL::check_unbalanced(AVLNode* root) {
    if (root == nullptr) return true;
    int cur = root->depth;
    calculate_depth(root);
    if (root->depth != cur) return false;
    if (abs(root->left_child_depth() - root->right_child_depth()) >= 2) return false;
    return check_unbalanced(root->childL) && check_unbalanced(root->childR);
}
