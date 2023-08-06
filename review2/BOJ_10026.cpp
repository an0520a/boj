#include <iostream>
#include <vector>
#include <array>
#include <queue>

typedef struct PointStruct
{
    size_t y;
    size_t x;
} Point;

int main()
{
    std::vector< std::vector<char> > map;
    std::vector< std::vector<bool> > visited;
    size_t N;
    size_t normal_count = 0, disable_count = 0;

    std::cin >> N;

    map.resize(N + 2);
    visited.resize(N + 2);
    for (size_t i = 0; i < N + 2; i++)
    {
        map[i].resize(N + 2);
        visited[i].resize(N + 2, false);
        visited[i][0] = true, visited[i][N + 1] = true;
    }
    std::fill(visited[0].begin(), visited[0].end(), true);
    std::fill(visited[N + 1].begin(), visited[N + 1].end(), true);

    for (size_t i = 1; i <= N; i++)
    {
        char buf[102];

        scanf(" %s", buf);

        std::move(buf, buf + N, map[i].begin() + 1);
    }

    for (size_t i = 1; i <= N; i++)
    {
        for (size_t j = 1; j <= N; j++)
        {
            if (visited[i][j] == false)
            {
                std::queue<Point> point_queue;
                char pre_clolor = map[i][j];
                normal_count++;

                visited[i][j] = true;
                point_queue.push({i, j});

                while(!point_queue.empty())
                {
                    Point p = point_queue.front();
                    point_queue.pop();

                    std::array<Point, 4> next_p_arr = 
                    { Point{p.y - 1, p.x}, {p.y + 1, p.x}, {p.y, p.x - 1}, {p.y, p.x + 1} };

                    for (const Point next_p : next_p_arr)
                    {
                        if (visited[next_p.y][next_p.x] == false && map[next_p.y][next_p.x] == pre_clolor)
                        {
                            visited[next_p.y][next_p.x] = true;
                            point_queue.push(next_p);
                        }
                    }
                }
            }
        }
    }

    for (size_t i = 1; i <= N; i++)
    {
        for (size_t j = 1; j <= N; j++)
        {
            if(map[i][j] == 'G')
            {
                map[i][j] = 'R';
            }
        }

        std::fill(visited[i].begin() + 1, visited[i].end() - 1, false);

    }

    for (size_t i = 1; i <= N; i++)
    {
        for (size_t j = 1; j <= N; j++)
        {
            if (visited[i][j] == false)
            {
                std::queue<Point> point_queue;
                char pre_clolor = map[i][j];
                disable_count++;

                visited[i][j] = true;
                point_queue.push({i, j});

                while(!point_queue.empty())
                {
                    Point p = point_queue.front();
                    point_queue.pop();

                    std::array<Point, 4> next_p_arr = 
                    { Point{p.y - 1, p.x}, {p.y + 1, p.x}, {p.y, p.x - 1}, {p.y, p.x + 1} };

                    for (const Point next_p : next_p_arr)
                    {
                        if (visited[next_p.y][next_p.x] == false && map[next_p.y][next_p.x] == pre_clolor)
                        {
                            visited[next_p.y][next_p.x] = true;
                            point_queue.push(next_p);
                        }
                    }
                }
            }
        }
    }

    std::cout << normal_count << ' ' << disable_count << std::endl;
}