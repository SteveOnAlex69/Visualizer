#ifndef BST_HPP
#define BST_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <utility>



struct BSTNode {
    int val;
    BSTNode* childL, * childR;
    BSTNode(int x = 0);
};

struct BST {
    BSTNode* root;

    BST();

    void insert(int x);
    void insert(BSTNode*& root, int x);
    void traverse();
    void traverse(BSTNode* root, std::vector<int>& ans);
    BSTNode* locate(int x);
    BSTNode* locate(BSTNode* root, int x);
    bool exist(int x);
    bool erase(int x);
    bool erase(BSTNode*& root, int x);
    int delete_left_most(BSTNode*& root);
};



#endif