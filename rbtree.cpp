#include <iostream>
#include "rbtree.h"

Node::Node(int value)
    : data(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}

RedBlackTree::RedBlackTree() {
    nil = new Node(0);
    nil->color = BLACK;
    nil->left = nil->right = nil->parent = nullptr;
    root = nil;
}

void RedBlackTree::rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != nil)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == nil)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void RedBlackTree::rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != nil)
        y->right->parent = x;

    y->parent = x->parent;
    if (x->parent == nil)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}

void RedBlackTree::insert(int data) {
    Node* z = new Node(data);
    z->left = z->right = z->parent = nil;

    Node* y = nil;
    Node* x = root;

    while (x != nil) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == nil)
        root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    z->left = z->right = nil;
    z->color = RED;

    fixInsert(z);
}

void RedBlackTree::fixInsert(Node* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotateLeft(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateRight(z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotateRight(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateLeft(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void RedBlackTree::remove(int data) {
    Node* z = searchNode(root, data);
    if (z != nil)
        deleteNode(z);
}

void RedBlackTree::deleteNode(Node* z) {
    Node* y = z;
    Node* x;
    bool yOriginalColor = y->color;

    if (z->left == nil) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nil) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = treeMinimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    delete z;

    if (yOriginalColor == BLACK)
        fixDelete(x);
}

void RedBlackTree::fixDelete(Node* x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft(x->parent);
                w = x->parent->right;
            }if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rotateRight(w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rotateLeft(x->parent);
                x = root;
            }
        } else {
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateRight(x->parent);
                w = x->parent->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft(w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rotateRight(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

Node* RedBlackTree::treeMinimum(Node* node) {
    while (node->left != nil)
        node = node->left;
    return node;
}

void RedBlackTree::transplant(Node* u, Node* v) {
    if (u->parent == nil)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    v->parent = u->parent;
}

Node* RedBlackTree::searchNode(Node* node, int key) const {
    while (node != nil && key != node->data) {
        if (key < node->data)
            node = node->left;
        else
            node = node->right;
    }
    return node;
}

bool RedBlackTree::search(int data) const {
    return searchNode(root, data) != nil;
}

void RedBlackTree::inOrder(Node* node) const {
    if (node != nil) {
        inOrder(node->left);
        std::cout << node->data << " ";
        inOrder(node->right);
    }
}

void RedBlackTree::printInOrder() const {
    inOrder(root);
    std::cout << std::endl;
}