#include <iostream>

#include "trie.hpp"

int main()
{
    trie T;

    T.insert("hello");
    T.insert("world");
    T.insert("white");

    std::cout << std::boolalpha << T.search("hello") << std::endl;
    std::cout << std::boolalpha << T.search("world") << std::endl;
    std::cout << std::boolalpha << T.search("he") << std::endl;
    std::cout << std::boolalpha << T.search("world1") << std::endl;

    T.print();
}