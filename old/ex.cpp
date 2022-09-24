#include <iostream>
#include <functional>

template < class T, class U=std::less_equal<T>>
class Test {
    public:
    T t;
    U u;
    Test() : t{}, u{} {}
    Test(T t, U u) : t{t}, u{u} {}
    ~Test() = default;
    bool isTest() const { return u(t, t); }
};

int main() {

    Test<int> pippo; 
    //std::cout<<pippo.t<<'\n';
    std::cout<<pippo.u(4,4)<<'\n'; // 0
    std::cout<<pippo.isTest()<<'\n';
    std::cout<<std::less<int>{}(4, 4)<<std::endl; //0


    Test<int, std::less<int>> pippa;

    std::cout<<pippo.u(4,4)<<'\n'; //0
    std::cout<<pippo.isTest()<<'\n';
    std::cout<<std::less_equal<int>{}(4, 4)<<std::endl; //1



    return 0;
}