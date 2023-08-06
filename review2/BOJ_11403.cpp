#include <iostream>
#include <queue>
#include <vector>

int main()
{
    size_t N;
    std::vector< std::vector<size_t> > graph;
    bool* visited_arr = nullptr;

    std::cin >> N;

    graph.resize(N + 1);
    visited_arr = new bool[N + 1];

    for (size_t i = 1; i <= N; i++)
    {
        for (size_t j = 1; j <= N; j++)
        {
            bool v;
            
            std::cin >> v;

            if (v == true)
            {
                graph[i].push_back(j);
            }
        }
    }

    for (size_t i = 1; i <= N; i++)
    {
        std::queue<size_t> vertex_queue;

        std::fill(visited_arr + 1, visited_arr + N + 1, false);

        vertex_queue.push(i);

        while (!vertex_queue.empty())
        {
            size_t v = vertex_queue.front();
            vertex_queue.pop();

            for (size_t next_v : graph[v])
            {
                if (visited_arr[next_v] == false)
                {
                    visited_arr[next_v] = true;
                    vertex_queue.push(next_v);
                }
            }
        }

        for (size_t v = 1; v <= N; v++)
        {
            if (visited_arr[v] == true)
            {
                std::cout << 1 << ' ';
            }
            else
            {
                std::cout << 0 << ' ';
            }
        }
        std::cout << std::endl;
    }

    delete[] visited_arr;
}