#include <iostream>
#include <queue>
#include <array>

typedef struct PointStruct
{
    size_t y;
    size_t x;
} Point;

int main()
{
    size_t n, m;
    std::queue<Point> point_queue;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;

    uint32_t (*dist_map)[m + 2] = 
    reinterpret_cast<uint32_t (*)[m + 2]>(operator new((n + 2) * (m + 2) * sizeof(uint32_t), std::align_val_t{alignof(uint32_t)}));
    bool (*visited_map)[m + 2] =
    reinterpret_cast<bool (*)[m + 2]>(operator new((n + 2) * (m + 2) * sizeof(bool), std::align_val_t{alignof(bool)}));

    std::fill(dist_map[0], dist_map[n + 2], 0);
    std::fill(visited_map[0], visited_map[0] + (m + 2), true);
    std::fill(visited_map[n + 1], visited_map[n + 1] + (m + 2), true);
    std::fill(visited_map[1], visited_map[n] + (m + 2), false);

    for (size_t i  = 1; i <= n; i++)
    {
        visited_map[i][0] = true, visited_map[i][m + 1] = true;

        for (size_t j = 1; j <= m; j++)
        {
            std::cin >> dist_map[i][j];

            if (dist_map[i][j] == 2)
            {
                visited_map[i][j] = true;
                point_queue.push(Point{i, j});
            }
            else if (dist_map[i][j] == 0)
            {
                visited_map[i][j] = true;
            }
        }
    }

    for (uint32_t dist = 0; !point_queue.empty(); dist++)
    {
        size_t point_queue_size = point_queue.size();

        for (size_t i = 0; i < point_queue_size; i++)
        {
            Point p = point_queue.front();
            point_queue.pop();
            
            dist_map[p.y][p.x] = dist;

            std::array<Point, 4> next_p_arr = { Point{p.y - 1, p.x}, {p.y + 1, p.x}, {p.y, p.x - 1}, {p.y, p.x + 1} };

            for (const Point& next_p : next_p_arr)
            {
                if (visited_map[next_p.y][next_p.x] == false)
                {
                    visited_map[next_p.y][next_p.x] = true;

                    point_queue.push(next_p);
                }
            }
        }
    }

    for (size_t i = 1; i <= n; i++)
    {
        for (size_t j = 1; j <= m; j++)
        {
            if (visited_map[i][j] == false && dist_map[i][j] == 1)
            {
                std::cout << -1 << ' ';
            }
            else
            {
                std::cout << dist_map[i][j] << ' ';
            }
        }

        std::cout << std::endl;
    }

    operator delete(dist_map);
    operator delete(visited_map);
}