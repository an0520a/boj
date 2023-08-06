#include <iostream>
#include <queue>
#include <vector>
#include <array>
#include <algorithm>

typedef struct StructPoint
{
    unsigned int y;
    unsigned int x;
} Point;

int main()
{
    unsigned int N;
    unsigned int count = 0;
    std::queue<Point> point_que;
    std::vector<unsigned int> size_vec;

    std::cin >> N;

    char (*map)[N + 2] = reinterpret_cast<char (*)[N + 2]>(operator new((N + 2) * (N + 2) * sizeof(char)));

    for (unsigned int i = 1; i <= N; i++)
    {
        scanf(" %s", map[i] + 1);
    }

    for (unsigned int i = 0; i < N + 2; i++)
    {
        map[0][i] = '0';
        map[N + 1][i] = '0';
        map[i][0] = '0';
        map[i][N + 1] = '0';
    }

    for (unsigned int i = 1; i <= N; i++)
    {
        for (unsigned int j = 1; j <= N; j++)
        {
            if (map[i][j] == '1')
            {
                count++;
                size_vec.push_back(0);

                map[i][j] = '0';
                point_que.push(Point{i, j});

                while (!point_que.empty())
                {
                    Point p = point_que.front();
                    point_que.pop();
                    size_vec.back()++;

                    std::array<Point, 4> next_p_arr = 
                    { Point{p.y - 1, p.x}, Point{p.y, p.x - 1}, Point{p.y + 1, p.x}, Point{p.y, p.x + 1} };

                    for (Point& next_p : next_p_arr)
                    {
                        if (map[next_p.y][next_p.x] == '1')
                        {
                            map[next_p.y][next_p.x] = '0';
                            point_que.push(next_p);
                        }
                    }
                }
            }
        }
    }

    std::sort(size_vec.begin(), size_vec.end());

    std::cout << count << std::endl;

    for (size_t size : size_vec)
    {
        std::cout << size << std::endl;
    }
}