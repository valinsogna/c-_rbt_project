# Red-Black Tree in c++
<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]

Implementation of Red-Black Tree class and its iterator in c++

## Compile and Run

- to compile type command `make`
- to run type command `./RBTree.x`
- to delete executable type command `make clean`

## Repository structure
You will find the implementation of the class Red-Black Tree and its iterator inside file `RBTree.cpp` along with a test inside the main. 

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

Implement the generic classes:
- `RBTree<T, CMP=std::less<T>>` to represent red-black trees.
- ` RBTree<T, CMP=std::less<T>>::const` to represent red-black trees constant iterators.

const iterator must provide the following public methods:
- `const T& operator*() const` to get the value associated to the iterator;
- `const T* operator->() const` to access to the value associated to the iterator;
- `const_iterator& operator++()` to pre-increment the iterator;
- `const_iterator operator++(int)` to post-increment the iterator;
- `bool operator==(const const_iterator&) const` to test whether two iterators are equivalent;
- `bool operator!=(const const_iterator&) const` to test whether two iterators are different.

Moreover, RBTree must provide the following public methods:
- `void insert(const T& value)` to insert a new value in the tree;
- `bool contains(const T& value) const` to test whether the tree con- tains a value;
- `bool delete(const T& value)` to delete a value from the tree;
- `RBTree<T, CMP>::const_iterator begin() const` to get a constant tree iterator over all the tree keys;
- `RBTree<T, CMP>::const_iterator end() const` to get the last value for a tree iterator. 

Few functions showing the classes features are also requested (e.g., by using the Boost test library).

## References
[1]: Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford Stein. Introduction to Algorithms. The MIT Press, 2nd edition, 2001

<!-- MARKDOWN LINKS & IMAGES -->

[contributors-shield]: https://img.shields.io/github/contributors/valinsogna/c-_rbt_project.svg?style=for-the-badge

[contributors-url]: https://github.com/valinsogna/c-_rbt_project/graphs/contributors

[forks-shield]: https://img.shields.io/github/forks/valinsogna/c-_rbt_project.svg?style=for-the-badge

[forks-url]: https://github.com/valinsogna/c-_rbt_project/network/members

[stars-shield]: https://img.shields.io/github/stars/valinsogna/c-_rbt_project.svg?style=for-the-badge

[stars-url]: https://github.com/valinsogna/c-_rbt_project/stargazers

[issues-shield]: https://img.shields.io/github/issues/valinsogna/c-_rbt_project.svg?style=for-the-badge

[issues-url]: https://github.com/valinsogna/c-_rbt_project/issues

[license-shield]: https://img.shields.io/github/license/valinsogna/c-_rbt_project.svg?style=for-the-badge

[license-url]: https://github.com/valinsogna/c-_rbt_project/blob/main/LICENSE