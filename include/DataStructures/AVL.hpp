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


class AVL {
public:
    AVLNode* root;

    AVL(bool is_self_balanced = false);
    void insert(int x);
    void traverse();
    AVLNode* search(int x);
    bool exist(int x);
    bool check_correct_depth();
    bool erase(int x);

    void clear();
private:
    void calculate_depth(AVLNode* x);
    int unbalanced(AVLNode* x);
    int delete_left_most(AVLNode*& root);
    bool erase(AVLNode*& root, int x);
    AVLNode* locate(AVLNode* root, int x);
    bool check_correct_depth(AVLNode* root);
    void traverse(AVLNode* root, std::vector<int>& ans);
    void insert(AVLNode*& root, int x);
    void rotate_left(AVLNode*& root);
    void rotate_right(AVLNode*& root);
    void correct(AVLNode*& root);


    void internal_clear(AVLNode* root);
    bool is_avl;
};



#endif