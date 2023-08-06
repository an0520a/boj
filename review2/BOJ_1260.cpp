#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

std::vector<size_t> DFS(const std::vector<std::vector<size_t>>& graph, size_t start_vertex);
std::vector<size_t> DFSCalc(const std::vector<std::vector<size_t>>& graph, bool* visited, size_t vertex);
std::vector<size_t> BFS(const std::vector<std::vector<size_t>>& graph, size_t start_vertex);

int main()
{
    size_t N, M, V;
    std::vector<std::vector<size_t>> graph;
    std::vector<size_t> order_vec;

    std::ios_base::sync_with_stdio(false);

    std::cin >> N >> M >> V;

    graph.resize(N + 1);

    for (size_t i = 0; i < M; i++)
    {
        size_t u, v;

        std::cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for (std::vector<size_t>& vec : graph)
    {
        std::sort(vec.begin(), vec.end());
    }

    order_vec = std::move(DFS(graph, V));
    for (size_t i : order_vec)
    {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    order_vec = std::move(BFS(graph, V));
    for (size_t i : order_vec)
    {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

std::vector<size_t> DFS(const std::vector<std::vector<size_t>>& graph, size_t start_vertex)
{
    bool* visited = new bool[graph.size()]{ false };
    visited[start_vertex] = true;

    std::vector<size_t> order_vec = std::move(DFSCalc(graph, visited, start_vertex));

    delete[] visited;

    return order_vec;
}

std::vector<size_t> DFSCalc(const std::vector<std::vector<size_t>>& graph, bool* visited, size_t vertex)
{
    std::vector<size_t> order_vec = { vertex };

    for (size_t next_v : graph[vertex])
    {
        if (visited[next_v] == false)
        {
            visited[next_v] = true;
            std::vector<size_t> tmp_vec = DFSCalc(graph, visited, next_v);
            order_vec.insert(order_vec.end(), tmp_vec.begin(), tmp_vec.end());
        }
    }

    return order_vec;
}

std::vector<size_t> BFS(const std::vector<std::vector<size_t>>& graph, size_t start_vertex)
{
    std::queue<size_t> vertex_queue;
    bool* visited = new bool[graph.size()]{ false };
    std::vector<size_t> order_vec;

    visited[start_vertex] = true;
    vertex_queue.push(start_vertex);
    order_vec.push_back(start_vertex);

    while(!vertex_queue.empty())
    {
        size_t v = vertex_queue.front();
        vertex_queue.pop();

        for (size_t next_v : graph[v])
        {
            if ( visited[next_v] == false)
            {
                visited[next_v] = true;
                vertex_queue.push(next_v);
                order_vec.push_back(next_v);
            }
        }
    }

    delete visited;

    return order_vec;
}