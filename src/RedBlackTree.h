#ifndef __RedBlackTree_H__
#define __RedBlackTree_H__

#include <memory> // for std::unique_ptr
#include <functional> // for std::less

enum class color : bool {black, red};
enum class side : bool {left, right};

// Class to represent Red-Black Tree with custom total order set as "less than"
template <typename T, typename CMP=std::less<T>>
class RBTree{
    // Class to represent Red-Black Tree Node
    class Node {
        T key;
        color color; 
        std::unique_ptr< Node > left;
        std::unique_ptr< Node > right;
        Node *parent;

        public:
        // default ctor
        Node(): color{color::black}, parent{nullptr}{}
        // custom ctors
        explicit Node(T& key) : key{key}, color{color::black}, parent{nullptr} {}
        explicit Node(T&& key) : key{std::move(key)}, color{color::black}, parent{nullptr} {}
        // default dtor
        ~Node() = default;

        // getters
        T getKey() const { return key; }
        color getColor() const { return color; }
        Node* getParent() const { return parent; }
        std::unique_ptr< Node > getLeft() const { return left; }
        std::unique_ptr< Node > getRight() const { return right; }

        // setters
        void setKey(T key) { this->key = key; }
        void setColor(color color) { if(this=nullptr) : this->color = color; } // NIL nodes are black
        void setLeft(std::unique_ptr< Node > left) { this->left.reset(left) ; } // TO EDIT?
        void setRight(std::unique_ptr< Node > right) { this->right.reset(right); } // TO EDIT?
        void setParent( Node *parent) { this->parent = parent; }

        // useful functions
        bool is_root() const { return parent == nullptr; }
        bool is_leaf() const { return left == nullptr && right == nullptr; }
        bool is_right_child() const { return !this->is_root() && parent->right == this; }

        Node* get_sibling() const { return is_right_child() ? parent->left : parent->right; }
        // gets the side of the node relative to its parent:
        side get_side() const { return is_right_child() ? side::right : side::left; }
        // reverse the side:
        side get_opposite_side() const { return !this.get_side(); }
        // gets the child on side s:
        Node* get_child(side s) const { return s == side::left ? left : right; }
        Node* get_uncle() const { return this->parent->get_sibling(); }
        Node* get_grandparent() const { return parent->parent; }

        // Used for BST insertion:
        void setChild(side s, std::unique_ptr< Node > child) { // TO EDIT?
            if (s == side::left) left = child; else right = child; 
            if (child) child->parent = this; 
        }
    };

    std::unique_ptr< Node > root;

    public:
    // default ctor
    RBTree(){}
    // default dtor
    ~RBTree() = default;
};

template <typename T>
void inorder_walk_aux(const std::unique_ptr< typename RBTree<T>::Node >);
template <typename T>
void inorder_walk(const RBTree<T>);

#endif //__RedBlackTree_H__