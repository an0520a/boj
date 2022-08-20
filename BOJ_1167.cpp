#include <cstdio>
#include <queue>
#include <vector>

typedef unsigned int u32;
typedef struct _entry
{
    u32 v;
    u32 w;
} entry;

entry getMaxWeightVertex(const std::vector<std::vector<entry>>& graph, u32 vertex);
void getMaxWeightVertexCMP(const std::vector<std::vector<entry>>& graph, bool* visited, u32* dist, u32 vertex);

int main()
{
    u32 n;
    std::vector<std::vector<entry>> graph;

    scanf(" %u", &n);

    graph.resize(n + 1);

    for (u32 i = 0; i < n; i++)
    {
        u32 u, v, w;

        scanf(" %u", &u);

        while(true)
        {
            scanf(" %u", &v);
            if(v == 0xFFFFFFFF) break;

            scanf(" %u", &w);

            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }
    }

    entry tmp = getMaxWeightVertex(graph, 1);
    tmp = getMaxWeightVertex(graph, tmp.v);

    printf("%u\n", tmp.w);
}

entry getMaxWeightVertex(const std::vector<std::vector<entry>>& graph, u32 vertex)
{
    bool *visited = new bool[graph.size()]{ false };
    u32 *dist = new u32[graph.size()]{ 0 };
    entry result = { 0, 0 };

    visited[vertex] = true;
    getMaxWeightVertexCMP(graph, visited, dist, vertex);

    for (u32 i = 1; i < graph.size(); i++) result = (result.w > dist[i])? result : entry({i, dist[i]});

    delete[] dist;
    delete[] visited;

    return result;
}

void getMaxWeightVertexCMP(const std::vector<std::vector<entry>>& graph, bool* visited, u32* dist, u32 vertex)
{
    for (u32 i = 0; i < graph[vertex].size(); i++)
    {
        if(visited[graph[vertex][i].v] == false)
        {
            visited[graph[vertex][i].v] = true;
            dist[graph[vertex][i].v] = dist[vertex] + graph[vertex][i].w;
            getMaxWeightVertexCMP(graph, visited, dist, graph[vertex][i].v);
        }
    }
}