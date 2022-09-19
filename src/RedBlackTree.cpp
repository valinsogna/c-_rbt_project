// Red Black Tree implementation in C++
// Author: Valeria Insogna

#include "RedBlackTree.h"
#include <iostream>

// Methods for RBTree class
template <typename T, typename CMP>
Node<T>* RBTree<T, CMP>::minimum_in_subtree(Node<T>* node) const {    
    if (!node) {
        return node;
    }
    while (node->left) {
        node = node->left.get();
    }
    return node;
}

template <typename T, typename CMP>
Node<T>* RBTree<T,CMP>::maximum_in_subtree(Node<T>* node) const {    
    if (!node) {
        return node;
    }
    while (node->right) {
        node = node->right.get();
    }
    return node;
}

template <typename T, typename CMP>
Node<T>* RBTree<T,CMP>::successor(const Node<T>* node) const{
    if (node->right) {
        return minimum_in_subtree(node->right);
    }
    Node<T>* parent = node->getParent();
    while (parent && node->is_right_child()) {
        node = parent;
        parent = parent->getParent();
    }
    return parent;
}

template <typename T, typename CMP>
const Node<T>* RBTree<T,CMP>::search_subtree(Node<T>* node, const T& key) const{
    if(!node || key == node->getKey())
        return node;
    if(cmp(key, node->getKey()))
        return search(node->getLeft().get(), key); //Check if .get() is needed
    else
        return search(node->getRight().get(), key); //Check if .get() is needed
}


// Useful functions
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