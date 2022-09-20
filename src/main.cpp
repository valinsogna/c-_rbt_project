#include <cassert>
#include <utility>
#include <numeric>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include "RedBlackTree.h"

// RBTree TESTS:
std::mt19937 gen(std::random_device{}());

int main() {
    constexpr size_t SIZE = 10000;
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

    std::cout << "Inserting " << SIZE << " elements:\n";
    std::cout << "unique ptr red-black tree : " << dt1.count() << " ms\n";

    if(SIZE<=100){
        std::cout << "\nInorder walk:\n";
        std::cout << rbtree << std::endl;
    }

    std::cout << "\nTry find : 7\n";
    auto it = std::find(rbtree.begin(), rbtree.end(), 7);
    if (it != rbtree.end())
      std::cout << "    Found " << *it << std::endl;
    else
      std::cout << "    Not found\n";

    std::cout << "\nTry find : 70\n";
    it = std::find(rbtree.begin(), rbtree.end(), 70);
    if (it != rbtree.end())
      std::cout << "    Found " << *it << std::endl;
    else
      std::cout << "    Not found\n";

    std::shuffle(v.begin(), v.end(), gen);

    t1 = std::chrono::steady_clock::now();
    for (auto n : v) {
        rbtree.Delete(n);
    }
    t2 = std::chrono::steady_clock::now();
    auto dt3 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);


    std::cout << "\nDeleting " << SIZE << " elements:\n";
    std::cout << "unique ptr red-black tree : " << dt3.count() << " ms\n";
    return 0;
}
