#include <iostream>

typedef long long i64;

typedef struct StructPoint
{
    int x;
    int y;
} Point;

int main()
{
    std::ios_base::sync_with_stdio(false);

    size_t N;
    Point* arr;
    i64 sum1 = 0;
    i64 sum2 = 0;

    std::cin >> N;

    arr = new Point[N + 1];

    for (size_t i = 0; i < N; i++)
    {
        std::cin >> arr[i].x >> arr[i].y;
    }

    for (size_t i = 0; i < N - 1; i++)
    {
        sum1 += (i64)arr[i].x * arr[i + 1].y;
        sum2 += (i64)arr[i + 1].x * arr[i].y;
    }

    sum1 += (i64)arr[N - 1].x * arr[0].y;
    sum2 += (i64)arr[0].x * arr[N - 1].y;

    std::cout << std::fixed;
    std::cout.precision(1);

    std::cout << (((sum1 > sum2)? sum1 - sum2 : sum2 - sum1) / 2.0);
}