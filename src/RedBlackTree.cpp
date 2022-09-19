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
    } else if (cmp(node->getKey(), y->getKey())) {
        y->setLeft(std::move(node));
    } else {
        y->setRight(std::move(node));
    }
    // Restore RB properties:
    node.setColour(Color::red);
    insert_fixup(std::move(node));
}

template <typename T, typename CMP>
void RBTree<T,CMP>::rotate(std::unique_ptr<Node<T>>&& x, side s){
    side r_s = get_reverse_side(s);
    auto y = std::move(x->get_child(r_s));
    auto removed_x = transplant( x.get(), std::move(y));
    auto beta = std::move(y->get_child(s));
    auto removed_y = transplant( beta.get(), std::move(y));
    x->setChild(r_s, std::move(beta));
    delete removed_x;
    delete removed_y;
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

template <typename T, typename CMP>
void RBTree<T,CMP>::insert_fixup(std::unique_ptr<Node<T>>&& node){
    while (!node->is_root() && node->parent->getColor() == Color::red) {
        auto uncle = node->get_uncle();
        if (uncle && uncle->getColor() == Color::red) {
            //Case 1: uncle is red
            node->parent->setColor(Color::black);
            uncle->setColor(Color::black);
            node->get_grandparent()->setColor(Color::red);
            node = node->get_grandparent();
        } else {
            if (node->get_side() != node->parent->get_side()) {
                //Case 2: uncle is black and node is outside
                node = node->parent;
                rotate(std::move(node), get_reverse_side(node->get_side()));
            }
            //Case 3: uncle is black and node is inside
            node->parent->setColor(Color::black);
            node->get_grandparent()->setColor(Color::red);
            rotate(std::move(node->get_grandparent()), get_reverse_side(node->get_side()));
        }
    }
    root->setColor(Color::black);
};


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