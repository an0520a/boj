#include <cstdio>
#include <memory.h>
#include <queue>
#include <array>

typedef struct PointStruct
{
    size_t y;
    size_t x;
} Point;

int main()
{
    size_t N, M;
    size_t count = 0;
    std::queue<Point> point_queue;

    scanf(" %lu %lu", &N, &M);

    char (*map)[M + 2] = reinterpret_cast<char (*)[M + 2]>(operator new((N + 2) * (M + 2) * sizeof(char)));

    memset(map[0], 'X', M + 2);
    memset(map[N + 1], 'X', M + 2);

    for (size_t i = 1, find_flag = false; i <= N; i++)
    {
        scanf(" %s", map[i] + 1);

        map[i][0] = 'X';
        map[i][M + 1] = 'X';

        if (find_flag == false)
        {
            for (size_t j = 1; j <= M; j++)
            {
                if (map[i][j] == 'I')
                {
                    point_queue.push({i, j});
                    map[i][j] = 'X';
                    find_flag = true;
                }
            }
        }
    }

    while (!point_queue.empty())
    {
        Point p = point_queue.front();
        point_queue.pop();

        std::array<Point, 4> next_p_array = 
        { Point{p.y - 1, p.x}, Point{p.y, p.x - 1}, Point{p.y + 1, p.x}, Point{p.y, p.x + 1} };

        for (Point next_p : next_p_array)
        {
            auto [y, x] = next_p;

            if (map[y][x] == 'O')
            {
                map[y][x] = 'X';
                point_queue.push(next_p);
            }
            else if (map[y][x] == 'P')
            {
                count++;
                map[y][x] = 'X';
                point_queue.push(next_p);
            }
        }
    }

    if (count == 0)
    {
        printf("TT\n");
    }
    else
    {
        printf("%lu\n", count);
    }

    operator delete(map);
}