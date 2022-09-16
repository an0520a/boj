#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>

typedef struct StructEdge
{
    size_t vertex;
    size_t weight;
} Edge;

std::vector<size_t> Dijkstra(const std::vector< std::vector<Edge> >& graph, size_t start_vertex);

int main()
{
    std::ios_base::sync_with_stdio(false);

    size_t n, m, r;
    std::vector< std::vector<Edge> > graph;
    std::vector<size_t> num_of_item_by_vertex_vec;
    size_t max_num_of_item = 0;

    std::cin >> n >> m >> r;

    num_of_item_by_vertex_vec.resize(n + 1);
    graph.resize(n + 1);

    for (size_t i = 1; i <= n; i++)
    {
        std::cin >> num_of_item_by_vertex_vec[i];
    }

    for (size_t i = 0; i < r; i++)
    {
        size_t u, v, w;

        std::cin >> u >> v >> w;

        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    for (size_t i = 1; i <= n; i++)
    {
        auto dist_vec = Dijkstra(graph, i);
        size_t num_of_item = 0;

        for (size_t j = 1; j <= n; j++)
        {
            if(dist_vec[j] <= m)
            {
                num_of_item += num_of_item_by_vertex_vec[j];
            }
        }

        max_num_of_item = std::max(max_num_of_item, num_of_item);
    }

    std::cout << max_num_of_item;
}

std::vector<size_t> Dijkstra(const std::vector< std::vector<Edge> >& graph, size_t start_vertex)
{
    auto edge_comp = [](const Edge& e1, const Edge& e2)->bool{return e1.weight > e2.weight;};
    std::vector<size_t> dist_vec(graph.size(), 0xFFFFFFFFFFFFFFFF);
    std::priority_queue<Edge, std::vector<Edge>, decltype(edge_comp)> que(edge_comp);
    bool* visited = new bool[graph.size()];
    memset(visited, false, graph.size() * sizeof(bool));

    dist_vec[start_vertex] = 0;
    que.push({start_vertex, 0});

    while(!que.empty())
    {
        Edge kEdge = que.top();
        que.pop();

        if(visited[kEdge.vertex] == false)
        {
            visited[kEdge.vertex] = true;

            for (Edge next_edge : graph[kEdge.vertex])
            {
                next_edge.weight += kEdge.weight;

                if(visited[next_edge.vertex] == false && next_edge.weight < dist_vec[next_edge.vertex])
                {
                    dist_vec[next_edge.vertex] = next_edge.weight;
                    que.push(next_edge);
                }
            }
        }
    }

    delete[] visited;

    return dist_vec;
}