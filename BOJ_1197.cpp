#include <iostream>
#include <vector>
#include <queue>

typedef unsigned int u32;

typedef struct StructEdge
{
    u32 v;
    int w;
} Edge;

int main()
{
    u32 V, E;
    std::vector< std::vector<Edge> > graph;
    constexpr auto edge_comp = [](const Edge& __x, const Edge& __y)->bool{ return __x.w > __y.w; };
    std::priority_queue<Edge, std::vector<Edge>, decltype(edge_comp)> que(edge_comp);
    int result = 0;

    std::ios_base::sync_with_stdio(false);
    std::cin >> V >> E;

    graph.resize(V + 1);
    for (size_t i = 0; i < E; i++)
    {
        u32 u, v;
        int w;

        std::cin >> u >> v >> w;

        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    std::vector<bool> visited(graph.size(), false);

    que.push({1, 0});

    while(!que.empty())
    {
        Edge edge = que.top();
        que.pop();

        if(visited[edge.v] == false)
        {
            result += edge.w;
            visited[edge.v] = true;

            for(Edge next_edge : graph[edge.v])
            {
                if(visited[next_edge.v] == false)
                    que.push(next_edge);
            }
        }
    }

    std::cout << result << std::endl;
}