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

    int get_tree_size();
};


class AVL {
public:
    AVLNode* root;

    AVL(bool is_self_balanced = false);
    void insert(int x);
    bool balance_the_tree();
    std::vector<void*> search_before_insert(int x);


    void traverse();
    std::vector<void*> search(int x);
    bool exist(int x);
    bool check_correct_depth();
    bool erase(int x);
    void clear();

private:
    void calculate_depth(AVLNode* x);
    int unbalanced(AVLNode* x);
    AVLNode* delete_left_most(AVLNode*& root);
    bool erase(AVLNode*& root, int x);
    void locate(AVLNode* root, int x, std::vector<void*> &ans);
    bool check_correct_depth(AVLNode* root);
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