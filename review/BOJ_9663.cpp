#include <cstdio>
#include <vector>
#include <memory.h>

typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct StructPoint
{
    int x;
    int y;
} Point;

u32 GetCaseOfNQueen(u32 N);
u32 GetCaseOfNQueenCalc(std::vector<Point>& queen_vec, u32 N);

int main()
{
    u32 N;

    scanf(" %u", &N);

    printf("%u\n", GetCaseOfNQueen(N));
}

u32 GetCaseOfNQueen(u32 N)
{
    std::vector<Point> queen_vec;

    return GetCaseOfNQueenCalc(queen_vec, N);
}

u32 GetCaseOfNQueenCalc(std::vector<Point>& queen_vec, u32 N)
{
    u32 result = 0;
    constexpr auto queen_matching = [](const std::vector<Point>& queen_vec, const Point& next_queen)->bool
    {
        constexpr auto abs = [](int x){ return (x >= 0)? x : -x; };

        for (Point pre_queen : queen_vec)
        {
            if(pre_queen.x == next_queen.x || pre_queen.y == next_queen.y || (pre_queen.x - pre_queen.y == next_queen.x - next_queen.y) || (abs(pre_queen.x - next_queen.x) == abs(pre_queen.y - next_queen.y)))
            {
                return true;
            }
        }
        
        return false;
    };

    if(queen_vec.size() == N) return 1;

    for (size_t i = 0; i < N; i++)
    {
        Point next_queen = { (int)queen_vec.size(), (int)i };

        if(queen_matching(queen_vec, next_queen) == false)
        {
            queen_vec.push_back(next_queen);

            result += GetCaseOfNQueenCalc(queen_vec, N);

            queen_vec.pop_back();
        }
    }

    return result;
}