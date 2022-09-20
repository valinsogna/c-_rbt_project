// Red Black Tree implementation in C++
// Author: Valeria Insogna
#include <iterator>
#include "RedBlackTree_iterator.h"
#include "RedBlackTree.h"

template <typename RBTree, typename T>
const_iterator<RBTree,T>& const_iterator<RBTree,T>::operator++() {  // pre-increment ++i
  current = current->next.get();
  return *this;
}

template <typename RBTree, typename T>
const_iterator<RBTree,T> const_iterator<RBTree,T>::operator++(int) {  // post-increment i++
  auto tmp = *this;
  ++(*this); // i++ is slower than ++i since it first return the copy and then increment it!
  return tmp;
}


