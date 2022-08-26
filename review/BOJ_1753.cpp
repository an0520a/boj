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

#define UINT_INF 0xFFFFFFFF

std::vector<u32> Dijkstra(const std::vector< std::vector<Edge> >& graph, u32 s);

int main()
{
    u32 V, E;
    u32 S;
    std::vector< std::vector<Edge> > graph;

    scanf(" %u %u", &V, &E);
    scanf(" %u", &S);

    graph.resize(V + 1);

    for (size_t i = 0; i < E; i++)
    {
        u32 u, v, c;

        scanf(" %u %u %u", &u, &v ,&c);

        graph[u].push_back(std::move(Edge{v, c}));
    }

    std::vector<u32> dist = Dijkstra(graph, S);

    for (size_t i = 1; i < graph.size(); i++)
    {
        if(dist[i] == UINT_INF) printf("INF\n");
        else                    printf("%u\n", dist[i]);
    }
}

std::vector<u32> Dijkstra(const std::vector< std::vector<Edge> >& graph, u32 s)
{
    std::vector<u32> dist(graph.size(), UINT_INF);
    bool* visited = new bool[graph.size()];
    memset(visited, false, graph.size() * sizeof(bool));
    constexpr auto min = [](const Edge& x, const Edge& y)->bool{ return x.w > y.w; };
    std::priority_queue<Edge, std::vector<Edge>, decltype(min)> que(min);

    que.push(std::move(Edge{s, 0}));

    while(!que.empty())
    {
        Edge edge = que.top();
        que.pop();

        if(visited[edge.v] == false)
        {
            visited[edge.v] = true;
            dist[edge.v] = edge.w;

            for (auto next_edge : graph[edge.v])
            {
                if(visited[next_edge.v] == false)
                {
                    next_edge.w += edge.w;
                    que.push(next_edge);
                }
            }
        }
    }

    delete[] visited;
    
    return dist;
}