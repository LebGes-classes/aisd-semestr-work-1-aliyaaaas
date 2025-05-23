#include "rbtree.h"

int main() {
    RedBlackTree tree;

    tree.insert(20);
    tree.insert(15);
    tree.insert(25);
    tree.insert(10);
    tree.insert(5);

    tree.printInOrder(); // должно вывести: 5 10 15 20 25

    tree.remove(15);
    tree.printInOrder(); // должно вывести: 5 10 20 25

    if (tree.search(10))
        std::cout << "нашлось 10\n";
    else
        std::cout << "10 не нашлось\n";

    return 0;
}