#ifndef AVL_HPP
#define AVL_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <utility>

struct AVLNode {
    int val, depth;
    AVLNode* childL, * childR;
    AVLNode(int x = 0);


    int left_child_depth();
    int right_child_depth();
    int check_unbalanced();
    int get_tree_size();
    int get_min();
};


class AVL {
public:
    AVLNode* root;

    AVL(bool is_self_balanced = false);
    void insert(int x);
    bool balance_the_tree();
    bool balance_deepest_node();
    std::vector<void*> search_before_insert(int x);
    std::vector<bool> search_before_insert_direction(int x);


    void traverse();
    std::vector<void*> search(int x);
    std::vector<bool> search_direction(int x);
    bool exist(int x);
    bool check_correct_depth();
    bool erase(int x);
    void clear();

    bool check_unbalanced();

private:
    void calculate_depth(AVLNode* x);
    int unbalanced(AVLNode* x);
    AVLNode* delete_left_most(AVLNode*& root);
    bool erase(AVLNode*& root, int x);
    bool check_correct_depth(AVLNode* root);
    bool check_unbalanced(AVLNode* root);
    void traverse(AVLNode* root, std::vector<int>& ans);
    void rotate_left(AVLNode*& root);
    void rotate_right(AVLNode*& root);
    bool correct(AVLNode*& root);


    void insert(AVLNode*& root, int x);
    bool balance_the_tree(AVLNode*& root);


    void internal_clear(AVLNode* root);
    bool is_avl;
};



#endif