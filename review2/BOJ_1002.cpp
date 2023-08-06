#include <iostream>

typedef struct PointStruct
{
    int x;
    int y;
    bool operator==(struct PointStruct _p) { return x == _p.x && y == _p.y; }
} Point;

unsigned int GetDistanceSquare(Point p1, Point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

int main()
{
    size_t T;

    std::cin >> T;

    for (size_t tc = 0; tc < T; tc++)
    {
        Point p1, p2;
        unsigned int r1, r2;

        std::cin >> p1.x >> p1.y >> r1 >> p2.x >> p2.y >> r2;

        if (r1 < r2)
        {
            std::swap(r1, r2);
            std::swap(p1, p2);
        }

        unsigned int pow_d = GetDistanceSquare(p1, p2);

        if (pow_d == 0)
        {
            if (r1 == r2)
            {
                std::cout << -1 << '\n';
            }
            else
            {
                std::cout << 0 << '\n';
            }
        }
        else if (pow_d == (r1 - r2) * (r1 - r2) || pow_d == (r1 + r2) * (r1 + r2))
        {
            std::cout << 1 << '\n';
        }
        else if (pow_d > (r1 + r2) * (r1 + r2) || pow_d < (r1 - r2) * (r1 - r2))
        {
            std::cout << 0 << '\n';
        }
        else
        {
            std::cout << 2 << '\n';
        }
    }
}