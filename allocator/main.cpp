#include <iostream>
#include "allocator.hpp"

struct node {
    node(double x): value(x), next(nullptr)
    {}
    double value;
    node * next;
};

int main()
{
    allocator<int> Ai{10};
    int *p1 = Ai.allocate(1);
    assert(p1 != nullptr);
    int *p2 = Ai.allocate(2);
    assert(p2 != nullptr);
    std::cout << *p1 << '\t' << *p2 << std::endl;
    Ai.deallocate(p1);
    Ai.deallocate(p2);

    allocator<node> An{3};
    node *n1 = An.allocate(1.1);
    assert(n1 != nullptr);
    std::cout << n1->value << std::endl;
    An.deallocate(n1);
    node *p[5];
    for (auto i = 0; i < 5; i++) {
        p[i] = An.allocate(1.2 + i);
        if (p[i]) {
            std::cout << p[i]->value << " at the " << i << "th block" << std::endl;
        }
    }
    for (auto i = 0; i < 5; i++) {
        if (p[i])
            An.deallocate(p[i]);
    }
}