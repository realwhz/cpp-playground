#include <unordered_set>
#include <iostream>

struct Point {
    int x;
    int y;
};

bool operator==(const Point& p1, const Point& p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

struct PointHash
{
    std::size_t operator() (const Point& p) const {
        return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
    }
};

int main()
{
    std::unordered_set<Point, PointHash> S{Point{0,1}, Point{1,1}, Point{1,0}, Point{2,0}};

    for ( const auto &p : S )
        std::cout << p.x << ',' << p.y << std::endl;

    std::cout << '\n';

    // note where the iterator is updated (by erase or ++it)
    for (auto it = S.begin(); it != S.end();) {
        if (it->x == 0)
            it = S.erase(it);
        else
            ++it;
    }

    // C++20
    //std::erase_if( S, []( const auto &p ) { return p.x == 0; } );

    for ( const auto &p : S)
        std::cout << p.x << ',' << p.y << std::endl;
}
