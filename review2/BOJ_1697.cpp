#include <iostream>
#include <queue>
#include <array>

int main()
{
    size_t N, M;
    size_t time = 0;
    std::array<bool, 100001> visited = { false };
    std::queue<size_t> pos_que;
    bool end_flag = false;

    std::cin >> N >> M;

    visited[N] = true;
    pos_que.push(N);

    while(true)
    {
        size_t pos_que_size = pos_que.size();

        for (size_t i = 0; i < pos_que_size; i++)
        {
            size_t pos = pos_que.front();
            pos_que.pop();

            std::array<size_t, 3> next_pos_arr = { pos - 1, pos + 1, pos * 2 };

            if (pos == M)
            {
                end_flag = true;
                break;
            }

            for (size_t next_pos : next_pos_arr)
            {
                if (next_pos <= 100000UL && visited[next_pos] == false)
                {
                    visited[next_pos] = true;
                    pos_que.push(next_pos);
                }
            }
        }

        if (end_flag)
        {
            break;
        }
        else
        {
            time++;
        }
    }

    std::cout << time << std::endl;
}