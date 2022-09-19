// Red Black Tree implementation in C++
// Author: Valeria Insogna

#include "RedBlackTree.h"

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

template <typename T, typename CMP>
void RBTree<T,CMP>::insert(std::unique_ptr<Node<T>> node){
    auto x = root.get();
    auto y = root.get();
    while (x != nullptr) {
        y = x;
        if (cmp(node->getKey(), x->getKey())) {
            if (cmp(x->getKey(), node->getKey())){
                throw Multi_insert{
                    "Cannot handle multiple insertions. You gave me " +
                    std::to_string(x->getKey())
                };
            }
            x = x->getLeft();
        } else {
            x = x->getRight();
        }
    }
    node->setParent(y);
    if (y == nullptr) {
        root.reset(node);
        x.setColour(Color::black);
    } else if (cmp(node->getKey(), y->getKey())) {
        y->setLeft(std::move(node));
        x.setColour(Color::red);
    } else {
        y->setRight(std::move(node));
        x.setColour(Color::red);
    }
    // Restore RB properties:
    insert_fixup(node);
}

template <typename T, typename CMP>
void RBTree<T,CMP>::insert(const T& key) {
    auto z = std::make_unique<Node<T>>(key);
    try {
        insert(std::move(z));
    } catch (const Multi_insert& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception. Aborting.\n";
        //std::abort();
    }
}

template <typename T, typename CMP>
Node<T>* RBTree<T,CMP>::transplant(Node<T>* x, std::unique_ptr<Node<T>>&& y){
    if (x->is_root()){
        root = std::move(y);
        if(y){
            y.setParent(nullptr);
        }
    } else {
        side x_side = x->get_side();
        x->getParent()->setChild(x_side, std::move(y));
    } 
    return x;
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