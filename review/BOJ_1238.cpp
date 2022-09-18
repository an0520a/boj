#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>

typedef unsigned int u32;

typedef struct StructEdge
{
    u32 v;
    u32 w;
} Edge;

std::vector<u32> Dijkstra(const std::vector< std::vector<Edge> >& graph, const u32& start_vertex);

int main()
{
    std::ios_base::sync_with_stdio(false);

    u32 N, M, X;
    u32 result = 0;
    std::vector< std::vector<Edge> > graph;
    std::vector< std::vector<Edge> > reverse_graph;

    std::cin >> N >> M >> X;

    graph.resize(N + 1);
    reverse_graph.resize(N + 1);

    for (size_t i = 0; i < M; i++)
    {
        u32 u, v, w;

        std::cin >> u >> v >> w;

        graph[u].push_back({v, w});
        reverse_graph[v].push_back({u, w});
    }

    const std::vector<u32> dist_go_to_x_vec = Dijkstra(reverse_graph, X);
    const std::vector<u32> dist_go_from_x_vec = Dijkstra(graph, X);

    for (size_t i = 1; i <= N; i++)
    {
        result = std::max(result, dist_go_to_x_vec[i] + dist_go_from_x_vec[i]);
    }

    std::cout << result << std::endl;
}

std::vector<u32> Dijkstra(const std::vector< std::vector<Edge> >& graph, const u32& start_vertex)
{
    auto edge_comp = [](const Edge& __x, const Edge& __y)->bool{ return __x.w > __y.w; };
    std::vector<u32> dist_vec(graph.size(), 0xFFFFFFFF);
    std::priority_queue<Edge, std::vector<Edge>, decltype(edge_comp)> que(edge_comp);
    bool* visited = new bool[graph.size()];
    memset(visited, false, graph.size() * sizeof(bool));

    que.push({start_vertex, 0});
    dist_vec[start_vertex] = 0;

    while(!que.empty())
    {
        Edge edge = que.top();
        que.pop();

        if(visited[edge.v] == false)
        {
            visited[edge.v] = true;

            for (Edge next_edge : graph[edge.v])
            {
                next_edge.w += edge.w;

                if(visited[next_edge.v] == false && next_edge.w < dist_vec[next_edge.v])
                {
                    dist_vec[next_edge.v] = next_edge.w;
                    que.push(next_edge);
                }
            }
        }
    }

    delete[] visited;

    return dist_vec;
}