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
};


struct AVL {
    AVLNode* root;

    AVL();
    void calculate_depth(AVLNode* x);
    int unbalanced(AVLNode* x);
    void insert(int x);
    void rotate_left(AVLNode*& root);
    void rotate_right(AVLNode*& root);
    void correct(AVLNode*& root);
    void insert(AVLNode*& root, int x);
    void traverse();
    void traverse(AVLNode* root, std::vector<int>& ans);
    AVLNode* locate(int x);
    AVLNode* locate(AVLNode* root, int x);
    bool exist(int x);
    bool check_correct_depth();
    bool check_correct_depth(AVLNode* root);
    bool erase(int x);
    bool erase(AVLNode*& root, int x);
    int delete_left_most(AVLNode*& root);
};



#endif