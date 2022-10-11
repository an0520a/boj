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

int main()
{
    u32 N, M;
    std::vector< std::vector<Edge> > graph;

    std::ios_base::sync_with_stdio(false);

    std::cin >> N >> M;

    graph.resize(N + 1);

    for (u32 i = 0; i < M; i++)
    {
        u32 A, B, C;

        std::cin >> A >> B >> C;

        graph[A].push_back({B, C});
        graph[B].push_back({A, C});
    }

    constexpr auto edge_comp = [](const Edge& __x, const Edge& __y)->bool{ return __x.w > __y.w; };
    std::vector<bool> visited(N + 1, false);
    std::vector<u32> edge_cost_vec;
    std::priority_queue<Edge, std::vector<Edge>, decltype(edge_comp)> que(edge_comp);

    que.push({1, 0});

    while(!que.empty())
    {
        Edge edge = que.top();
        que.pop();

        if (visited[edge.v] == false)
        {
            visited[edge.v] = true;
            edge_cost_vec.push_back(edge.w);

            for (const Edge& next_edge : graph[edge.v])
            {
                if (visited[next_edge.v] == false)
                {
                    que.push(next_edge);
                }
            }
        }
    }

    u32 result = 0;
    u32 max = 0;

    for (const u32& edge_cost : edge_cost_vec)
    {
        max = std::max(max, edge_cost);
        result += edge_cost;
    }

    result -= max;

    std::cout << result << std::endl;
}