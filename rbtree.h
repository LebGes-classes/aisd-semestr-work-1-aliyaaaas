#define rbtree_h
#include <iostream>

enum Color {RED, BLACK};

struct Node {
    int data;
    bool color;
    Node* left;
    Node* right;
    Node* parent;

    Node(int value);
};

class RedBlackTree {
private:
    Node* root;
    Node* nil;
    void rotateLeft(Node* x);
    void rotateRight(Node* x);
    void fixInsert(Node* z);
    void fixDelete(Node* x);
    void transplant(Node* u, Node* v);
    Node* treeMinimum(Node* node);
    Node* searchNode(Node* node, int key) const;
    void deleteNode(Node* z);
    void inOrder(Node* node) const;

public:
    RedBlackTree();
    void insert(int data);
    void remove(int data);
    bool search(int data) const;
    void printInOrder() const;
};