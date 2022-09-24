#ifndef __RedBlackTree_HPP__
#define __RedBlackTree_HPP__

#include <memory> // for std::unique_ptr
#include <functional> // for std::less
#include <string>
#include <iostream>

enum class Color : bool {black, red};
enum class side : bool {left, right};
inline side get_reverse_side(const side s) { return s == side::right? side::left : side::right; };

struct Multi_insert {
    std::string message;
    Multi_insert(std::string s) : message{std::move(s)} {}
    const char* what() const { return message.c_str(); }
};

// Struct to represent Red-Black Tree Node
template <typename T>
struct Node {
    T key;
    Color color; 
    std::unique_ptr< Node<T> > left;
    std::unique_ptr< Node<T> > right;
    Node<T> *parent;

    public:
    // default ctor
    Node() noexcept : color{Color::red}, parent{nullptr}{}
    // custom ctors
    explicit Node(const T& key) noexcept : key{key}, color{Color::red}, parent{nullptr} {}
    explicit Node(T&& key) noexcept : key{std::move(key)}, color{Color::red}, parent{nullptr} {}
    // default dtor
    ~Node() noexcept = default;

    // useful methods
    bool is_root() const { return parent == nullptr; }
    bool is_leaf() const { return left == nullptr && right == nullptr; }
    bool is_right_child() const { return !this->is_root() && parent->right == this; }
    side get_side() const { return is_right_child() ? side::right : side::left; }
};

template <typename RBTree, typename T>
class const_iterator {
    RBTree* current;

    public:
    // From <iterator> we must specify:
    using value_type = T; 
    using reference = value_type&;
    using pointer = value_type*;
    using difference_type = std::ptrdiff_t; //#include <iterator>
    using iterator_category = std::forward_iterator_tag; // we didn't implement operator--, only ++

    explicit const_iterator(RBTree* x) : current{x} {} //ctor
    //const on right for status not changing assurance:
    reference operator*() const { return current->key; } //old: T&
    const_iterator& operator++();  // pre-increment ++i
    const_iterator operator++(int); // post-increment i++
    friend bool operator==(const const_iterator& x, const const_iterator& y) {
          return x.current == y.current;
    }
    friend bool operator!=(const const_iterator& x, const const_iterator& y) {
          return !(x == y); // We can call the operator== since it is friend instead of:
      // x.current != y.current;
    }
};

// Class to represent Red-Black Tree
template <typename T, typename CMP=std::less<T>>
class RBTree {
    public:
    std::unique_ptr< Node<T>> root;
    CMP cmp;

    private:
    // PRIVATE METHODS
    Node<T>* search_subtree(Node<T>*, const T&) const;
    void insert(std::unique_ptr<Node<T>>);
    // Replace x by y in the tree. It returns the ptr to the removed x:
    Node<T>* transplant(Node<T>* x, std::unique_ptr<Node<T>>&& y);
    void rotate_left(std::unique_ptr<Node<T>>&&);
    void rotate_right(std::unique_ptr<Node<T>>&&);
    void insert_fixup(std::unique_ptr<Node<T>>&&);
    void delete_fixup(Node<T>*, Node<T>*);
    // Delete a node form a Binary Search tree:
    Node<T>* Delete_BTS(Node<T>* );
    // Delete a node form a Red Black tree:
    bool Delete(Node<T>*);

    public:
    // ctor
    RBTree() noexcept {}
    // default dtor
    ~RBTree() noexcept = default;

    using _iterator = const_iterator<Node<T>, const T>; //const ref returned
    auto begin() const { return _iterator{root.get()}; } 
    auto end() const { return _iterator{nullptr}; }

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

// To print the tree in-order-walk:
template <typename T>
std::ostream& operator<<(std::ostream&, Node<T>*);
template <typename T, typename CMP>
std::ostream& operator<<(std::ostream&, const RBTree<T,CMP>&);

#endif //__RedBlackTree_HPP__