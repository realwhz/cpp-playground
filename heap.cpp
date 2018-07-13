// I implement a max heap
// The functionality is the same as STL's make_heap

#include <iostream>
#include <algorithm>
#include <vector>

size_t left(size_t i)
{
    return 2*i+1;
}

size_t right(size_t i)
{
    return 2*i+2;
}

size_t parent(size_t i)
{
    if (i == 0)
        return 0;
    return (i-1)/2;
}

void heapify(std::vector<int>& nums, size_t i)
{
    size_t largest = i;
    size_t l = left(i);
    size_t r = right(i);

    if (l < nums.size() && nums[l] > nums[i])
        largest = l;
    else
        largest = i;
    if (r < nums.size() && nums[r] > nums[largest])
        largest = r;
    if (largest != i) {
        std::swap(nums[i], nums[largest]);
        heapify(nums, largest);
    }
}

void build_heap(std::vector<int>& nums)
{
    if (nums.size() <= 1)
        return;
    
    for (size_t i = nums.size()/2-1; i != 0; --i) {
        heapify(nums, i);
    }
    heapify(nums, 0);
}
 
int main()
{
    std::vector<int> v { 3, 1, 4, 1, 5, 9 };
    std::vector<int> v2 = v;
 
    std::cout << "initially, v: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';
 
    std::make_heap(v.begin(), v.end());
 
    std::cout << "after make_heap, v: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';
 
    std::pop_heap(v.begin(), v.end());
    auto largest = v.back();
    v.pop_back();
    std::cout << "largest element: " << largest << '\n';
 
    std::cout << "after removing the largest element, v: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';
    
    std::cout << "try my solution\n";
    std::cout << "initially, v2: ";
    for (auto i : v2) std::cout << i << ' ';
    std::cout << '\n';
    std::vector<int> v2 { 3, 1, 4, 1, 5, 9 };
    build_heap(v2);
    std::cout << "after build_heap, v2: ";
    for (auto i : v2) std::cout << i << ' ';
    std::cout << '\n';
}
