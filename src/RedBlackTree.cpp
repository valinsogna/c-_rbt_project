// Red Black Tree implementation in C++
// Author: Valeria Insogna

#include "RedBlackTree.h"
#include <iostream>

template <typename T>
void inorder_walk_aux(const std::unique_ptr< Node<T> > node) {
    if (node == nullptr) return;
    inorder_walk_aux(node->getLeft());
    std::cout << node->getKey() << " ";
    inorder_walk_aux(node->getRight());
}

template <typename T>
void inorder_walk(const RBTree<T> tree) {
    inorder_walk_aux(tree.root->getLeft());
    std::cout << tree.root->getKey() << " ";
    inorder_walk_aux(tree.root->getRight());
}