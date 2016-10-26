#include <iterator>
#include <functional>
#include <algorithm>

#include <vector>
#include <iostream>

template<typename BiIt, typename Pred>
BiIt find_first_of(BiIt first, BiIt last, Pred p)
{
    return std::find_if(first, last, p);
}

template<typename BiIt, typename Pred>
BiIt find_last_of(BiIt first, BiIt last, Pred p)
{
    // We demo how to convert iterator and its corresponding revert_iterator back and forth
    std::reverse_iterator<BiIt> rfirst {last};
    std::reverse_iterator<BiIt> rlast {first};

    auto x = std::find_if(rfirst, rlast, p);

    // base() will convert a reverse_iterator to its iterator counterpart but will have one element shift
    return std::prev(x.base());
}

template<typename BiIt, typename Pred>
BiIt mypartition(BiIt first, BiIt last, Pred p)
{
    // using template alias to avoid tedious typing
    // it is better than typedef because no need to use `typename'
    using Value_type = typename std::iterator_traits<BiIt>::value_type;

    // if p is a lambda, in order to use not1, must create a function object
    std::function<bool(Value_type)> q = p;

    BiIt it1 = find_first_of(first, last, std::not1(q));
    BiIt it2 = find_last_of(first, last, p);

    while (it1 < it2) {
        std::iter_swap(it1, it2);
        // alternatively, we can create another lambda to achieve the same effect of not1
        it1 = find_first_of(first, last, [&p](Value_type x){ return !p(x); });
        it2 = find_last_of(first, last, p);
    }

    return it1;
}

int main()
{
    std::vector<int> v {5, 2, 2, 3, 1, 3, 4, 5};
    std::cout << *find_last_of(v.begin(), v.end(), [](int x) { return x < 2;}) << '\n';
    
    auto x = mypartition(v.begin(), v.end(), [](int x) { return x < 2;});
    for (auto i : v)
        std::cout << i << ' ';
    std::cout << '\n' << *x << '\n';
}
