#include <iostream>
#include <queue>
#include <array>
#include <bitset>

int main()
{
    unsigned int N, M;
    unsigned int time = 0;
    std::bitset<100001> visited = { false };
    std::array<unsigned int, 100001> path_size_arr = { 0 };
    std::queue<unsigned int> pos_que;
    bool find_flag = false;

    std::cin >> N >> M;

    visited[N] = true;
    path_size_arr[N] = true;

    pos_que.push(N);

    while (!pos_que.empty())
    {
        unsigned int pos_que_size = pos_que.size();

        for (unsigned int i = 0; i < pos_que_size; i++)
        {
            unsigned int p = pos_que.front();
            pos_que.pop();

            if (p == M)
            {
                find_flag = true;
                break;
            }

            std::array<unsigned int, 3> next_p_array = { p - 1, p + 1, 2 * p };

            for (const unsigned int next_p : next_p_array)
            {
                if (next_p <= 100000 && visited[next_p] == false)
                {
                    if (path_size_arr[next_p] == 0)
                    {
                        pos_que.push(next_p);
                    }

                    path_size_arr[next_p] += path_size_arr[p];
                }
            }
        }

        pos_que_size = pos_que.size();

        for (unsigned int i = 0; i < pos_que_size; i++)
        {
            unsigned int p = pos_que.front();
            pos_que.pop();
            pos_que.push(p);

            visited[p] = true;
        }

        if (find_flag == true)
        {
            break;
        }
        else
        {
            time++;
        }
    }
    
    std::cout << time << std::endl;
    std::cout << path_size_arr[M] << std::endl;
}