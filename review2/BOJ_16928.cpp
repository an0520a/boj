#include <iostream>
#include <queue>
#include <array>

int main()
{
    size_t time = 0;
    size_t N, M;
    bool visited[101] = { true };
    uint32_t path[101] = { 0 };
    std::queue<uint32_t> point_queue;

    std::cin >> N >> M;

    for (uint32_t i = 1; i <= 100; i++)
    {
        path[i] = i;
    }

    for (size_t i = 0; i < N + M; i++)
    {
        uint32_t u, v;

        std::cin >> u >> v;

        path[u] = v;
    }

    point_queue.push(1);

    bool end_flag = false;

    while (!point_queue.empty())
    {
        size_t point_queue_size = point_queue.size();

        for (size_t i = 0; i < point_queue_size; i++)
        {
            uint32_t p = point_queue.front();
            point_queue.pop();

            if (p == 100)
            {
                end_flag = true;
                break;
            }

            for (uint32_t i = 1; i <= 6 && p + i <= 100; i++)
            {
                uint32_t next_p = p + i;

                if (path[next_p] != next_p)
                {
                    visited[next_p] = true;
                }

                next_p = path[next_p];

                if (visited[next_p] == false)
                {
                    visited[next_p] = true;
                    point_queue.push(next_p);
                }
            }
        }

        if (end_flag)
        {
            break;
        }

        time++;
    }

    std::cout << time << std::endl;
}