#include <iostream>
#include <queue>
#include <array>

struct Point
{
    size_t y;
    size_t x;
};

int main()
{
    
    size_t N, M;
    std::queue<Point> point_que;
    size_t time = 0;
    bool find_flag = false;

    std::cin >> N >> M;

    char (*map)[M + 2] = reinterpret_cast<char (*)[M + 2]>(operator new((N + 2) * (M + 2) * sizeof(char)));

    for (size_t i = 1; i <= N; i++)
    {
        scanf(" %s", map[i] + 1);
    }

    for (size_t i = 0; i < M + 2; i++)
    {
        map[0][i] = '0';
        map[N + 1][i] = '0';
    }
    for (size_t i = 1; i <= N; i++)
    {
        map[i][0] = '0';
        map[i][M + 1] = '0';
    }

    point_que.push({1, 1});
    map[1][1] = '0';

    while (find_flag == false)
    {
        const size_t que_size = point_que.size();

        for (size_t i = 0; i < que_size; i++)
        {
            Point p = point_que.front();
            point_que.pop();

            const auto [y, x] = p;

            if(y == N && x == M)
            {
                find_flag = true;
                break;
            }

            std::array<Point, 4> next_p_arr
            = { Point{y - 1, x}, Point{y, x - 1}, Point{y + 1, x}, Point{y, x + 1} };

            for (const Point& next_p : next_p_arr)
            {
                if(map[next_p.y][next_p.x] == '1')
                {
                    map[next_p.y][next_p.x] = '0';
                    point_que.push(next_p);
                }
            }

            
        }

        time++;
    }

    std::cout << time << std::endl;

    operator delete(map);
}