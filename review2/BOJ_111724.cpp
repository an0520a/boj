#include <iostream>
#include <vector>
#include <queue>

int main()
{
    size_t number_of_vertices, number_of_edges;
    std::vector< std::vector<size_t> > graph;
    bool* visited_arr = nullptr;
    size_t count = 0;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> number_of_vertices >> number_of_edges;

    graph.resize(number_of_vertices + 1);
    visited_arr = new bool[number_of_vertices + 1]{ false };

    for (size_t i = 0; i < number_of_edges; i++)
    {
        size_t u, v;

        std::cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for (size_t i = 1; i <= number_of_vertices; i++)
    {
        if (visited_arr[i] == false)
        {
            count++;

            std::queue<size_t> vertex_queue;

            visited_arr[i] = true;
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
        }
    }

    delete[] visited_arr;

    std::cout << count << std::endl;
}