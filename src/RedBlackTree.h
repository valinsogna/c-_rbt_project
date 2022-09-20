#ifndef __RedBlackTree_H__
#define __RedBlackTree_H__

#include <memory> // for std::unique_ptr
#include <functional> // for std::less
#include <string>
#include <iostream>

enum class Color : bool {black, red};
enum class side : bool {left, right};
side get_reverse_side(const side s) { return s == side::right? side::left : side::right; };

struct Multi_insert {
    std::string message;
    Multi_insert(std::string s) : message{std::move(s)} {}
    const char* what() const { return message.c_str(); }
};

// Class to represent Red-Black Tree Node
template <typename T>
class Node {
    T key;
    Color color; 
    std::unique_ptr< Node<T> > left;
    std::unique_ptr< Node<T> > right;
    Node<T> *parent;

    public:
    // default ctor
    Node() noexcept : color{Color::black}, parent{nullptr}{}
    // custom ctors
    explicit Node(const T& key) noexcept : key{key}, color{Color::black}, parent{nullptr} {}
    explicit Node(T&& key) noexcept : key{std::move(key)}, color{Color::black}, parent{nullptr} {}
    // default dtor
    ~Node() noexcept = default;

    // getters
    T getKey() const { return key; }
    Color getColor() const { return color; }
    Node<T>* getParent() const { return parent; }
    std::unique_ptr< Node<T> > getLeft() const { return left; }
    std::unique_ptr< Node<T> > getRight() const { return right; }

    // setters
    void setKey(const T& key) { this->key = key; }
    void setColor(const Color col) { this=nullptr? this->color = Color::black : this->color = col; } // NIL nodes are black
    void setLeft(std::unique_ptr< Node<T> > left) { this->left.reset(left) ; } // Use std::move to call this function on a smart ptr
    void setRight(std::unique_ptr< Node<T> > right) { this->right.reset(right); } // Use std::move to call this function on a smart ptr
    void setParent( Node<T> *parent) { this->parent = parent; }
    void setChild(side s, std::unique_ptr< Node<T> > child) { // Use std::move to call this function on a smart ptr
        if (s == side::left) left.reset(child); else right.reset(child);
        if (child) child->parent = this; 
    }

    // useful functions
    bool is_root() const { return parent == nullptr; }
    bool is_leaf() const { return left == nullptr && right == nullptr; }
    bool is_right_child() const { return !this->is_root() && parent->right == this; }
    
    std::unique_ptr<Node<T>> get_sibling() const { return is_right_child() ? parent->left : parent->right; }
    // gets the side of the node relative to its parent:
    side get_side() const { return is_right_child() ? side::right : side::left; }
    // reverse the side:
    side get_opposite_side() const { return !this->get_side(); }
    // gets the child on side s:
    std::unique_ptr<Node<T>> get_child(side s) const { return s == side::left ? left : right; }
    std::unique_ptr<Node<T>> get_uncle() const { return this->parent->get_sibling(); }
    Node<T>* get_grandparent() const { return parent->parent; }
};

// Class to represent Red-Black Tree
template <typename T, typename CMP=std::less<T>()>
class RBTree {
    std::unique_ptr< Node<T>> root;
    CMP cmp;

    // PRIVATE METHODS
    Node<T>* search_subtree(Node<T>*, const T&) const;
    void insert(std::unique_ptr<Node<T>>);
    // Replace x by y in the tree. It returns the ptr to the removed x:
    Node<T>* transplant(Node<T>* x, std::unique_ptr<Node<T>>&& y);
    void rotate(std::unique_ptr<Node<T>>&& x, side s);
    void insert_fixup(std::unique_ptr<Node<T>>&&);
    void delete_fixup(std::unique_ptr<Node<T>>&&);
    // Delete a node form a Binary Search tree:
    Node<T>* Delete_BTS(Node<T>* );
    // Delete a node form a Red Black tree:
    bool Delete(Node<T>*);

    public:
    // ctor
    RBTree() noexcept : cmp{std::less<T>()}{}
    // default dtor
    ~RBTree() noexcept = default;

    // PUBLIC METHODS
    Node<T>* minimum_in_subtree(Node<T>*) const;
    Node<T>* maximum_in_subtree(Node<T>*) const;
    Node<T>* successor(const Node<T>*) const;

    // To search a value from the tree:
    Node<T>* search_subtree(const T& key) const{ return search_subtree(root.get(), key);};

    // To insert a new value in the tree:
    void insert(const T&);

    // To test whether the tree contains a value:
    bool contains(const T& key) const{ return search_subtree(key) != nullptr;}; 

    // To delete a value from the tree:      
    bool Delete(const T& key) {
        auto z = search_subtree(key);
        return Delete(z);
    }
};

template <typename T, typename CMP>
void inorder_walk_aux(const std::unique_ptr< typename RBTree<T,CMP>::Node >);
template <typename T, typename CMP>
void inorder_walk(const RBTree<T,CMP>);
template <typename T>
std::ostream& operator<<(std::ostream&, Node<T>*);
template <typename T, typename CMP>
std::ostream& operator<<(std::ostream&, const RBTree<T,CMP>&);

#endif //__RedBlackTree_H__