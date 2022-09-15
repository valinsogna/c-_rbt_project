#ifndef __RedBlackTree_H__
#define __RedBlackTree_H__

#include <memory> // for unique_ptr

enum class color : bool {black, red};
enum class side : bool {left, right};

// Class to represent Red-Black Tree Node
template <typename T>
class Node {
    T key;
    color color; 
    std::unique_ptr< Node<T> > left;
    std::unique_ptr< Node<T> > right;
    Node<T> *parent;

    public:
    // default ctor
    Node(): color{color::black},left{nullptr}, right{nullptr}, parent{nullptr}{}
    // custom ctor
    explicit Node(T key) : key{key}, color{color::black}, left{nullptr}, right{nullptr}, parent{nullptr} {}
    // default dtor
    ~Node() = default;

    // getters
    T getKey() const { return key; }
    color getColor() const { return color; }
    Node<T>* getParent() const { return parent; }
    std::unique_ptr< Node<T> > getLeft() const { return left; }
    std::unique_ptr< Node<T> > getRight() const { return right; }

    // setters
    void setKey(T key) { this->key = key; }
    void setColor(color color) { if(this=nullptr) : this->color = color; } // NIL nodes are black
    // void setLeft(std::unique_ptr< Node<T> > left) { this->left = std::make_unique<Node>(std::move(left)); }
    // void setRight(std::unique_ptr< Node<T> > right) { this->right = right; }
    void setParent( Node<T> *parent) { this->parent = parent; }

    // useful functions
    bool is_root() const { return parent == nullptr; }
    bool is_leaf() const { return left == nullptr && right == nullptr; }
    bool is_right_child() const { return !this->is_root() && parent->right == this; }
    
    Node<T>* get_sibling() const { return is_right_child() ? parent->left : parent->right; }
    // gets the side of the node relative to its parent:
    side get_side() const { return is_right_child() ? side::right : side::left; }
    // reverse the side:
    side get_opposite_side() const { return !this.get_side(); }
    // gets the child on side s:
    Node<T>* get_child(const side s) const { return s == side::left ? left : right; }
    Node<T>* get_uncle() const { return this->parent->get_sibling(); }
    Node<T>* get_grandparent() const { return parent->parent; }

    void setChild(const side s, Node<T>* child) { 
        if (s == side::left) left = child; else right = child; 
        if (child) child->parent = this; 
    }
};

// Class to represent Red-Black Tree
template <typename T>
class RBTree{
    std::unique_ptr< Node<T> > root;

    public:
    // default ctor
    RBTree() { root = nullptr; }
};

template <typename T>
void inorder_walk_aux(const std::unique_ptr< Node<T> >);
template <typename T>
void inorder_walk(const RBTree<T>);

#endif //__RedBlackTree_H__