Implementation of Red-Black Tree class and its iterator in c++

## Introduction
Red-Black Trees are binary search trees satisfying the following conditions:
- every node is either red or black;
- the root is black
- every leaf (NIL) is black;
- if a node is red, then its children are black;
- for each node x, all the simple paths from x to descendant leaves contains the same number of black nodes.

Thanks to the mentioned properties, it is possible to insert, delete, and
search a value in a red-black tree in time O(log n) (e.g., see [1]).

## Implementation
```cpp
Implement the generic classes:
- RBTree<T, CMP=std::less<T>> 
- RBTree<T, CMP=std::less<T>>::const iterator to represent red-black trees and their constant iterators.

const iterator must provide the following public methods:
- const T& operator*() const to get the value associated to the iterator;
- const T* operator->() const to access to the value associated to the iterator;
- const_iterator& operator++() to pre-increment the iterator;
- const_iterator operator++(int) to post-increment the iterator;
- bool operator==(const const_iterator&) const to test whether two iterators are equivalent;
- bool operator!=(const const_iterator&) const to test whether two iterators are different.

Moreover, RBTree must provide the following public methods:
- void insert(const T& value) to insert a new value in the tree;
- bool contains(const T& value) const to test whether the tree con- tains a value;
- bool delete(const T& value) to delete a value from the tree;
- RBTree<T, CMP>::const_iterator begin() const to get a constant tree iterator over all the tree keys;
- RBTree<T, CMP>::const_iterator end() const to get the last value for a tree iterator. 

Few functions showing the classes features are also requested (e.g., by using the Boost test library).
