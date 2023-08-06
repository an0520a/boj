#include <iostream>
#include <vector>
#include <queue>

int main()
{
    std::vector< std::vector<size_t> > graph;
    size_t N, M;
    bool* visited = nullptr;
    std::queue<size_t> pos_queue;
    size_t count = 0;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> N >> M;

    graph.resize(N + 1);
    
    for (size_t i = 0; i < M; i++)
    {
        size_t u, v;

        std::cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    visited = new bool[N + 1]{ false };

    pos_queue.push(1);
    visited[1] = true;

    while (!pos_queue.empty())
    {
        size_t p = pos_queue.front();
        pos_queue.pop();

        for (size_t next_p : graph[p])
        {
            if (visited[next_p] == false)
            {
                visited[next_p] = true;
                pos_queue.push(next_p);
                count++;
            }
        }
    }

    std::cout << count << std::endl;
}