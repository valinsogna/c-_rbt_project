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
#include "RedBlackTree.h"

//Fast pseudo-random number generator
std::mt19937 gen(std::random_device{}());

int main() {
    constexpr size_t SIZE = 10;//100'000;
    std::vector<int> v (SIZE);
    //Fills the range [first, last) with sequentially increasing values, starting with 1:
    std::iota(v.begin(), v.end(), 1);
    //Rearranges the elements in the range [first,last) randomly, using g as uniform random number generator:
    std::shuffle(v.begin(), v.end(), gen);
    RBTree<int,std::less<int>> rbtree;
    auto t1 = std::chrono::steady_clock::now();
    for (auto n : v) {
        rbtree.insert(n);
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

    std::cout << "Print tree:\n";
    std::cout << rbtree << std::endl;

    std::cout << "Find : 7\n";
    auto it = std::find(rbtree.begin(), rbtree.end(), 7);
    if (it != rbtree.end())
      std::cout << "Found " << *it << std::endl;

    std::cout << "Find : 70\n";
    it = std::find(rbtree.begin(), rbtree.end(), 70);
    if (it != rbtree.end())
      std::cout << "Found " << *it << std::endl;


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