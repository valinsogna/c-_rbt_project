#ifndef __RedBlackTree_iterator_H__
#define __RedBlackTree_iterator_H__

#include "RedBlackTree.h"

//RED BLACK TREE ITERATOR CLASS METHODS
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

    explicit _iterator(RBTree* x) : current{x} {} //ctor
    //const on right for status not changing assurance:
    reference operator*() const { return current->value; } //old: T&
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


#endif //__RedBlackTree_iterator_H__