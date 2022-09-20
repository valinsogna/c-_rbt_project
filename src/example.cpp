#include <cassert>
#include <iostream>
#include <memory>
#include <utility>
#include <numeric>
#include <vector>
#include <random>
#include <set>
#include <chrono>
#include <algorithm>

std::mt19937 gen(std::random_device{}());

enum class Color {
    Red,
    Black
};

template <typename T>
struct Node {
    T key;
    Color color;
    std::unique_ptr<Node<T>> left;
    std::unique_ptr<Node<T>> right;
    Node<T>* parent;

    Node(const T& key) : key {key}, color {Color::Red}, parent {nullptr} {}
};

template <typename T>
struct RBTree {
public:
    std::unique_ptr<Node<T>> root;

private:
    void LeftRotate(std::unique_ptr<Node<T>>&& x) {
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

    void RightRotate(std::unique_ptr<Node<T>>&& x) {
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

public:
    Node<T>* Search(const T& key) {
        return Search(root.get(), key);
    }

    void Insert(const T& key) {
        auto z = std::make_unique<Node<T>>(key);
        Insert(std::move(z));
    }

    void Delete(const T& key) {
        auto z = Search(key);
        Delete(z);
    }

private:
    Node<T>* Search(Node<T>* x, const T& key) {
        if (!x || x->key == key) {
            return x;
        }
        if (key < x->key) {
            return Search(x->left.get(), key);
        } else {
            return Search(x->right.get(), key);
        }
    }

    void Insert(std::unique_ptr<Node<T>> z) {
        Node<T>* y = nullptr;
        Node<T>* x = root.get();
        while (x) {
            y = x;
            if (z->key < x->key) {
                x = x->left.get();
            } else {
                x = x->right.get();
            }
        }
        z->parent = y;
        if (!y) {
            root = std::move(z);
            InsertFixup(std::move(root));
        } else if (z->key < y->key) {
            y->left = std::move(z);
            InsertFixup(std::move(y->left));
        } else {
            y->right = std::move(z);
            InsertFixup(std::move(y->right));
        }
    }

    void InsertFixup(std::unique_ptr<Node<T>>&& z) {
        auto zp = z->parent;
        while (zp && zp->color == Color::Red) {
            auto zpp = zp->parent;
            if (zp == zpp->left.get()) {
                auto y = zpp->right.get();
                if (y && y->color == Color::Red) {
                    zp->color = Color::Black;
                    y->color = Color::Black;
                    zpp->color = Color::Red;
                    zp = zpp->parent;
                } else {
                    if (z == zp->right) {
                        LeftRotate(std::move(zpp->left));
                        zp = zpp->left.get();
                    }
                    zp->color = Color::Black;
                    zpp->color = Color::Red;
                    auto zppp = zpp->parent;
                    if (!zppp) {
                        RightRotate(std::move(root));
                    } else if (zpp == zppp->left.get()) {
                        RightRotate(std::move(zppp->left));
                    } else {
                        RightRotate(std::move(zppp->right));
                    }
                }
            } else {
                auto y = zpp->left.get();
                if (y && y->color == Color::Red) {
                    zp->color = Color::Black;
                    y->color = Color::Black;
                    zpp->color = Color::Red;
                    zp = zpp->parent;
                } else {
                    if (z == zp->left) {
                        RightRotate(std::move(zpp->right));
                        zp = zpp->right.get();
                    }
                    zp->color = Color::Black;
                    zpp->color = Color::Red;
                    auto zppp = zpp->parent;
                    if (!zppp) {
                        LeftRotate(std::move(root));
                    } else if (zpp == zppp->left.get()) {
                        LeftRotate(std::move(zppp->left));
                    } else {
                        LeftRotate(std::move(zppp->right));
                    }
                }
            }
        }
        root->color = Color::Black;
    }

    Node<T>* Transplant(Node<T>* u, std::unique_ptr<Node<T>>&& v) {
        if (v) {
            v->parent = u->parent;
        }
        Node<T>* w = nullptr;
        if (!u->parent) {
            w = root.release();
            root = std::move(v);
        } else if (u == u->parent->left.get()) {
            w = u->parent->left.release();
            u->parent->left = std::move(v);
        } else {
            w = u->parent->right.release();
            u->parent->right = std::move(v);
        }
        return w;
    }

    Node<T>* Minimum(Node<T>* x) {
        if (!x) {
            return x;
        }
        while (x->left) {
            x = x->left.get();
        }
        return x;
    }

    void Delete(Node<T>* z) {
        if (!z) {
            return;
        }
        Color orig_color = z->color;
        Node<T>* x = nullptr;
        Node<T>* xp = nullptr;
        if (!z->left) {
            x = z->right.get();
            xp = z->parent;
            delete Transplant(z, std::move(z->right));
        } else if (!z->right) {
            x = z->left.get();
            xp = z->parent;
            auto pz = Transplant(z, std::move(z->left));
            auto upz = std::unique_ptr<Node<T>>(pz);
        } else {
            auto y = Minimum(z->right.get());
            orig_color = y->color;
            x = y->right.get();
            xp = y;
            if (y->parent == z) {
                if (x) {
                    x->parent = y;
                }
                auto pz = Transplant(z, std::move(z->right));
                y->left = std::move(pz->left);
                y->left->parent = y;
                y->color = pz->color;
                auto upz = std::unique_ptr<Node<T>>(pz);
            } else {
                xp = y->parent;
                auto py = Transplant(y, std::move(y->right));
                py->right = std::move(z->right);
                py->right->parent = py;
                auto upy = std::unique_ptr<Node<T>>(py);
                auto pz = Transplant(z, std::move(upy));
                py->left = std::move(pz->left);
                py->left->parent = py;
                py->color = pz->color;
                auto upz = std::unique_ptr<Node<T>>(pz);
            }
        }
        if (orig_color == Color::Black) {
            DeleteFixup(x, xp);
        }
    }

    void DeleteFixup(Node<T>* x, Node<T>* xp) {
        while (x != root.get() && (!x || x->color == Color::Black)) {
            if (x == xp->left.get()) {
                Node<T>* w = xp->right.get();
                if (w && w->color == Color::Red) {
                    w->color = Color::Black;
                    xp->color = Color::Red;
                    auto xpp = xp->parent;
                    if (!xpp) {
                        LeftRotate(std::move(root));
                    } else if (xp == xpp->left.get()) {
                        LeftRotate(std::move(xpp->left));
                    } else {
                        LeftRotate(std::move(xpp->right));
                    }
                    w = xp->right.get();
                }
                if (w && (!w->left || w->left->color == Color::Black)
                    && (!w->right || w->right->color == Color::Black)) {
                    w->color = Color::Red;
                    x = xp;
                    xp = xp->parent;
                } else if (w) {
                    if (!w->right || w->right->color == Color::Black) {
                        w->left->color = Color::Black;
                        w->color = Color::Red;
                        auto wp = w->parent;
                        if (!wp) {
                            RightRotate(std::move(root));
                        } else if (w == wp->left.get()) {
                            RightRotate(std::move(wp->left));
                        } else {
                            RightRotate(std::move(wp->right));
                        }
                        w = xp->right.get();
                    }
                    w->color = xp->color;
                    xp->color = Color::Black;
                    w->right->color = Color::Black;
                    auto xpp = xp->parent;
                    if (!xpp) {
                        LeftRotate(std::move(root));
                    } else if (xp == xpp->left.get()) {
                        LeftRotate(std::move(xpp->left));
                    } else {
                        LeftRotate(std::move(xpp->right));
                    }
                    x = root.get();
                } else {
                    x = root.get();
                }
            } else {
                Node<T>* w = xp->left.get();
                if (w && w->color == Color::Red) {
                    w->color = Color::Black;
                    xp->color = Color::Red;
                    auto xpp = xp->parent;
                    if (!xpp) {
                        RightRotate(std::move(root));
                    } else if (xp == xpp->left.get()) {
                        RightRotate(std::move(xpp->left));
                    } else {
                        RightRotate(std::move(xpp->right));
                    }
                    w = xp->left.get();
                }
                if (w && (!w->left || w->left->color == Color::Black)
                    && (!w->right || w->right->color == Color::Black)) {
                    w->color = Color::Red;
                    x = xp;
                    xp = xp->parent;
                } else if (w) {
                    if (!w->left || w->left->color == Color::Black) {
                        w->right->color = Color::Black;
                        w->color = Color::Red;
                        auto wp = w->parent;
                        if (!wp) {
                            LeftRotate(std::move(root));
                        } else if (w == wp->left.get()) {
                            LeftRotate(std::move(wp->left));
                        } else {
                            LeftRotate(std::move(wp->right));
                        }
                        w = xp->left.get();
                    }
                    w->color = xp->color;
                    xp->color = Color::Black;
                    w->left->color = Color::Black;
                    auto xpp = xp->parent;
                    if (!xpp) {
                        RightRotate(std::move(root));
                    } else if (xp == xpp->left.get()) {
                        RightRotate(std::move(xpp->left));
                    } else {
                        RightRotate(std::move(xpp->right));
                    }
                    x = root.get();
                } else {
                    x = root.get();
                }
            }
        }
        if (x) {
            x->color = Color::Black;
        }
    }

};

template <typename T>
std::ostream& operator<<(std::ostream& os, Node<T>* node) {
    if (node) {
        os << node->left.get();
        os << node->key;
        if (node->color == Color::Black) {
            os << "● ";
        } else {
            os << "○ ";
        }
        os << node->right.get();
    }
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const RBTree<T>& tree) {
    os << tree.root.get();
    return os;
}

int main() {
    constexpr size_t SIZE = 100;//100'000;
    std::vector<int> v (SIZE);
    std::iota(v.begin(), v.end(), 1);
    std::shuffle(v.begin(), v.end(), gen);
    RBTree<int> rbtree;
    auto t1 = std::chrono::steady_clock::now();
    for (auto n : v) {
        //std::cout << n <<std::endl;
        rbtree.Insert(n);
    }
    auto t2 = std::chrono::steady_clock::now();
    auto dt1 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    std::set<int> rbset;
    t1 = std::chrono::steady_clock::now();
    for (auto n : v) {
        rbset.insert(n);
    }
    t2 = std::chrono::steady_clock::now();
    auto dt2 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    std::cout << "Inserting " << SIZE << " elements:\n";
    std::cout << "unique ptr red-black tree : " << dt1.count() << " ms\n";
    std::cout << "standard red-black tree : " << dt2.count() << " ms\n";

    std::cout << rbtree << std::endl;

    std::shuffle(v.begin(), v.end(), gen);

    t1 = std::chrono::steady_clock::now();
    for (auto n : v) {
        rbtree.Delete(n);
    }
    t2 = std::chrono::steady_clock::now();
    auto dt3 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    t1 = std::chrono::steady_clock::now();
    for (auto n : v) {
        rbset.erase(n);
    }
    t2 = std::chrono::steady_clock::now();
    auto dt4 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    std::cout << "Deleting " << SIZE << " elements:\n";
    std::cout << "unique ptr red-black tree : " << dt3.count() << " ms\n";
    std::cout << "standard red-black tree : " << dt4.count() << " ms\n";

}