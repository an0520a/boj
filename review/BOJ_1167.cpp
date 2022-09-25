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

Edge GetFarthestVertex(const std::vector< std::vector<Edge> >& graph, u32 s);
void GetFarthestVertexComp(const std::vector< std::vector<Edge> >& graph, bool* visited, Edge edge, Edge& max_edge);

int main()
{
    u32 V;
    std::vector< std::vector<Edge> > graph;
    Edge result;

    std::ios_base::sync_with_stdio(false);

    std::cin >> V;

    graph.resize(V + 1);

    for (size_t i = 0; i < V; i++)
    {
        u32 u, v, w;

        std::cin >> u;

        while (true)
        {
            std::cin >> v;

            if (v == 0xFFFFFFFF) break;

            std::cin >> w;

            graph[u].push_back({v, w});
        }
    }

    result = GetFarthestVertex(graph, 1);
    result = GetFarthestVertex(graph, result.v);

    std::cout << result.w;
}

Edge GetFarthestVertex(const std::vector< std::vector<Edge> >& graph, u32 s)
{
    bool* visited = new bool[graph.size()];
    memset(visited, false, graph.size() * sizeof(bool));
    Edge max_value = {s, 0};

    GetFarthestVertexComp(graph, visited, {s, 0}, max_value);

    delete[] visited;

    return max_value;
}

void GetFarthestVertexComp(const std::vector< std::vector<Edge> >& graph, bool* visited, Edge edge, Edge& max_edge)
{
    visited[edge.v] = true;
    max_edge = (max_edge.w > edge.w)? max_edge : edge;

    for(Edge next_edge : graph[edge.v])
    {
        next_edge.w += edge.w;

        if(visited[next_edge.v] == false)
        {
            GetFarthestVertexComp(graph, visited, next_edge, max_edge);
        }
    }
}