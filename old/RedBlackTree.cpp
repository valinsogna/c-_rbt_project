// Red Black Tree implementation in C++
// Author: Valeria Insogna

#include "RedBlackTree.hpp"

// RBTree PUBLIC METHODS
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
    Node<T>* parent = node->parent;
    while (parent && node->is_right_child()) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
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


// RBTree PRIVATE METHODS
template <typename T, typename CMP>
Node<T>* RBTree<T,CMP>::search_subtree(Node<T>* node, const T& key) const{
    if(!node || key == node->key)
        return node;
    if(cmp(key, node->key))
        return search_subtree(node->left.get(), key);
    else
        return search_subtree(node->right.get(), key);
}

template <typename T, typename CMP>
void RBTree<T,CMP>::insert(std::unique_ptr<Node<T>> node){
    Node<T>* x = root.get();
    Node<T>* y = root.get();
    while (x) {
        y = x;
        if (cmp(node->key, x->key)) {
            if (cmp(x->key, node->key)){
                throw Multi_insert{
                    "Cannot handle multiple insertions. You gave me " +
                    std::to_string(x->key)
                };
            }
            x = x->left.get();
        } else {
            x = x->right.get();
        }
    }
    node->parent = y;
    // Restore RB properties:
    if (!y) {
        root = std::move(node);
        insert_fixup(std::move(root));
    } else if (cmp(node->key, y->key)) {
        y->left = std::move(node);
        insert_fixup(std::move(y->left));
    } else {
        y->right = std::move(node);
        insert_fixup(std::move(y->right));
    }
}

template <typename T, typename CMP>
void RBTree<T,CMP>::rotate_left(std::unique_ptr<Node<T>>&& x){
    auto y = std::move(x->right);
    x->right = std::move(y->left);
    if (x->right) {
        x->right->parent = x.get();
    }
    y->parent = x->parent;
    auto xp = x->parent;
    if (!xp) {
        auto px = x.release();
        root = std::move(y);
        root->left = std::unique_ptr<Node<T>>(px);
        root->left->parent = root.get();
    } else if (x == xp->left) {
        auto px = x.release();
        xp->left = std::move(y);
        xp->left->left = std::unique_ptr<Node<T>>(px);
        xp->left->left->parent = xp->left.get();
    } else {
        auto px = x.release();
        xp->right = std::move(y);
        xp->right->left = std::unique_ptr<Node<T>>(px);
        xp->right->left->parent = xp->right.get();
    }
}

template <typename T, typename CMP>
void RBTree<T,CMP>::rotate_right(std::unique_ptr<Node<T>>&& x){
    auto y = std::move(x->left);
    x->left = std::move(y->right);
    if (x->left) {
        x->left->parent = x.get();
    }
    y->parent = x->parent;
    auto xp = x->parent;
    if (!xp) {
        auto px = x.release();
        root = std::move(y);
        root->right = std::unique_ptr<Node<T>>(px);
        root->right->parent = root.get();
    } else if (x == xp->left) {
        auto px = x.release();
        xp->left = std::move(y);
        xp->left->right = std::unique_ptr<Node<T>>(px);
        xp->left->right->parent = xp->left.get();
    } else {
        auto px = x.release();
        xp->right = std::move(y);
        xp->right->right = std::unique_ptr<Node<T>>(px);
        xp->right->right->parent = xp->right.get();
    }
}

template <typename T, typename CMP>
void RBTree<T,CMP>::insert_fixup(std::unique_ptr<Node<T>>&& z){
    auto zp = z->parent;
    while (zp && zp->color == Color::red) {
        auto zpp = zp->parent;
        if (zp == zpp->left.get()) {
            auto y = zpp->right.get();
            if (y && y->color == Color::red) {
                zp->color = Color::black;
                y->color = Color::black;
                zpp->color = Color::red;
                zp = zpp->parent;
            } else {
                if (z == zp->right) {
                    rotate_left(std::move(zpp->left));
                    zp = zpp->left.get();
                }
                zp->color = Color::black;
                zpp->color = Color::red;
                auto zppp = zpp->parent;
                if (!zppp) {
                    rotate_right(std::move(root));
                } else if (zpp == zppp->left.get()) {
                    rotate_right(std::move(zppp->left));
                } else {
                    rotate_right(std::move(zppp->right));
                }
            }
        } else {
            auto y = zpp->left.get();
            if (y && y->color == Color::red) {
                zp->color = Color::black;
                y->color = Color::black;
                zpp->color = Color::red;
                zp = zpp->parent;
            } else {
                if (z == zp->left) {
                    rotate_right(std::move(zpp->right));
                    zp = zpp->right.get();
                }
                zp->color = Color::black;
                zpp->color = Color::red;
                auto zppp = zpp->parent;
                if (!zppp) {
                    rotate_left(std::move(root));
                } else if (zpp == zppp->left.get()) {
                    rotate_left(std::move(zppp->left));
                } else {
                    rotate_left(std::move(zppp->right));
                }
            }
        }
    }
    root->color = Color::black;
};

template <typename T, typename CMP>
Node<T>* RBTree<T,CMP>::transplant(Node<T>* x, std::unique_ptr<Node<T>>&& y){
    if (y) {
        y->parent = x->parent;
    }
    Node<T>* w = nullptr;
    if (!x->parent) {
        w = root.release();
        root = std::move(y);
    } else if (x == x->parent->left.get()) {
        w = x->parent->left.release();
        x->parent->left = std::move(y);
    } else {
        w = x->parent->right.release();
        x->parent->right = std::move(y);
    }
    return w;
}

template <typename T, typename CMP>
bool RBTree<T,CMP>::Delete(Node<T>* z){
    if (!z) {
        return false;
    }
    Color orig_color = z->color;
    Node<T>* x = nullptr;
    Node<T>* xp = nullptr;
    if (!z->left) {
        x = z->right.get();
        xp = z->parent;
        delete transplant(z, std::move(z->right));
    } else if (!z->right) {
        x = z->left.get();
        xp = z->parent;
        auto pz = transplant(z, std::move(z->left));
        auto upz = std::unique_ptr<Node<T>>(pz);
    } else {
        auto y = minimum_in_subtree(z->right.get());
        orig_color = y->color;
        x = y->right.get();
        xp = y;
        if (y->parent == z) {
            if (x) {
                x->parent = y;
            }
            auto pz = transplant(z, std::move(z->right));
            y->left = std::move(pz->left);
            y->left->parent = y;
            y->color = pz->color;
            auto upz = std::unique_ptr<Node<T>>(pz);
        } else {
            xp = y->parent;
            auto py = transplant(y, std::move(y->right));
            py->right = std::move(z->right);
            py->right->parent = py;
            auto upy = std::unique_ptr<Node<T>>(py);
            auto pz = transplant(z, std::move(upy));
            py->left = std::move(pz->left);
            py->left->parent = py;
            py->color = pz->color;
            auto upz = std::unique_ptr<Node<T>>(pz);
        }
    }
    if (orig_color == Color::black) {
        delete_fixup(x, xp);
    }
    return true;
}

template <typename T, typename CMP>
void RBTree<T,CMP>::delete_fixup(Node<T>* x, Node<T>* xp){
    while (x != root.get() && (!x || x->color == Color::black)) {
        if (x == xp->left.get()) {
            Node<T>* w = xp->right.get();
            if (w && w->color == Color::red) {
                w->color = Color::black;
                xp->color = Color::red;
                auto xpp = xp->parent;
                if (!xpp) {
                    rotate_left(std::move(root));
                } else if (xp == xpp->left.get()) {
                    rotate_left(std::move(xpp->left));
                } else {
                    rotate_left(std::move(xpp->right));
                }
                w = xp->right.get();
            }
            if (w && (!w->left || w->left->color == Color::black)
                && (!w->right || w->right->color == Color::black)) {
                w->color = Color::red;
                x = xp;
                xp = xp->parent;
            } else if (w) {
                if (!w->right || w->right->color == Color::black) {
                    w->left->color = Color::black;
                    w->color = Color::red;
                    auto wp = w->parent;
                    if (!wp) {
                        rotate_right(std::move(root));
                    } else if (w == wp->left.get()) {
                        rotate_right(std::move(wp->left));
                    } else {
                        rotate_right(std::move(wp->right));
                    }
                    w = xp->right.get();
                }
                w->color = xp->color;
                xp->color = Color::black;
                w->right->color = Color::black;
                auto xpp = xp->parent;
                if (!xpp) {
                    rotate_left(std::move(root));
                } else if (xp == xpp->left.get()) {
                    rotate_left(std::move(xpp->left));
                } else {
                    rotate_left(std::move(xpp->right));
                }
                x = root.get();
            } else {
                x = root.get();
            }
        } else {
            Node<T>* w = xp->left.get();
            if (w && w->color == Color::red) {
                w->color = Color::black;
                xp->color = Color::red;
                auto xpp = xp->parent;
                if (!xpp) {
                    rotate_right(std::move(root));
                } else if (xp == xpp->left.get()) {
                    rotate_right(std::move(xpp->left));
                } else {
                    rotate_right(std::move(xpp->right));
                }
                w = xp->left.get();
            }
            if (w && (!w->left || w->left->color == Color::black)
                && (!w->right || w->right->color == Color::black)) {
                w->color = Color::red;
                x = xp;
                xp = xp->parent;
            } else if (w) {
                if (!w->left || w->left->color == Color::black) {
                    w->right->color = Color::black;
                    w->color = Color::red;
                    auto wp = w->parent;
                    if (!wp) {
                        rotate_left(std::move(root));
                    } else if (w == wp->left.get()) {
                        rotate_left(std::move(wp->left));
                    } else {
                        rotate_left(std::move(wp->right));
                    }
                    w = xp->left.get();
                }
                w->color = xp->color;
                xp->color = Color::black;
                w->left->color = Color::black;
                auto xpp = xp->parent;
                if (!xpp) {
                    rotate_right(std::move(root));
                } else if (xp == xpp->left.get()) {
                    rotate_right(std::move(xpp->left));
                } else {
                    rotate_right(std::move(xpp->right));
                }
                x = root.get();
            } else {
                x = root.get();
            }
        }
    }
    if (x) {
        x->color = Color::black;
    }
}    


// USEFUL FUNCTIONS TO PRINT RBTree:
template <typename T>
std::ostream& operator<<(std::ostream& os, Node<T>* node) {
    if (node) {
        os << node->left.get();
        os << node->key;
        if (node->color == Color::black) {
            os << "● ";
        } else {
            os << "○ ";
        }
        os << node->right.get();
    }
    return os;
}

template <typename T, typename CMP>
std::ostream& operator<<(std::ostream& os, const RBTree<T,CMP>& tree) {
    os << tree.root.get();
    return os;
}


// RBTree ITERATOR:
template <typename RBTree, typename T>
const_iterator<RBTree,T>& const_iterator<RBTree,T>::operator++() {  // pre-increment ++i
  current = current->right.get();
  return *this;
}

template <typename RBTree, typename T>
const_iterator<RBTree,T> const_iterator<RBTree,T>::operator++(int) {  // post-increment i++
  auto tmp = *this;
  ++(*this); // i++ is slower than ++i since it first return the copy and then increment it!
  return tmp;
}
