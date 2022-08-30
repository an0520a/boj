#include <cstdio>
#include <vector>
#include <memory.h>

typedef unsigned int u32;
typedef struct StructEdge
{
    u32 v;
    u32 w;
} Edge;

Edge GetMaxLength(const std::vector< std::vector<Edge> >& graph, u32 s);
Edge GetMaxLengthComp(const std::vector< std::vector<Edge> >& graph, Edge edge, bool* visited);

int main()
{
    u32 num_of_nodes;
    std::vector< std::vector<Edge> > graph;
    Edge result;

    scanf(" %u", &num_of_nodes);

    graph.resize(num_of_nodes + 1);

    for (size_t i = 1; i < num_of_nodes; i++)
    {
        u32 u, v, w;

        scanf(" %u %u %u", &u, &v, &w);

        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    result = GetMaxLength(graph, 1);
    result = GetMaxLength(graph, result.v);

    printf("%u\n", result.w);
}

Edge GetMaxLength(const std::vector< std::vector<Edge> >& graph, u32 s)
{
    bool* visited = new bool[graph.size()];
    memset(visited, false, graph.size() * sizeof(bool));

    visited[s] = true;
    Edge result = GetMaxLengthComp(graph, {s, 0}, visited);

    delete[] visited;

    return result;
}

Edge GetMaxLengthComp(const std::vector< std::vector<Edge> >& graph, Edge edge, bool* visited)
{
    Edge max_edge = edge;
    
    for (Edge next_edge : graph[edge.v])
    {
        if(visited[next_edge.v] == false)
        {
            visited[next_edge.v] = true;
            next_edge.w += edge.w;

            Edge recursion_result = GetMaxLengthComp(graph, next_edge, visited);
            max_edge = (max_edge.w > recursion_result.w)? max_edge : recursion_result;
        }
    }

    return max_edge;
}