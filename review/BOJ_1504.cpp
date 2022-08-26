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

std::vector<u32> Dijkstra(const std::vector< std::vector<Edge> >& graph, u32 s);
u32 GetDist(const std::vector< std::vector<Edge> >& graph, u32 u, u32 v);


int main()
{
    u32 N, E;
    std::vector< std::vector<Edge> > graph;
    u32 v1, v2;

    scanf(" %u %u", &N, &E);

    graph.resize(N + 1);

    for (size_t i = 0; i < E; i++)
    {
        u32 u, v, c;

        scanf(" %u %u %u", &u, &v ,&c);

        graph[u].push_back(std::move(Edge{v, c}));
        graph[v].push_back(std::move(Edge{u, c}));
    }

    scanf(" %u %u", &v1, &v2);

    std::vector<u32> dist_1 = Dijkstra(graph, 1);

    if(dist_1[v1] == 0xFFFFFFFF || dist_1[v2] == 0xFFFFFFFF || dist_1[N] == 0xFFFFFFFF) printf("-1\n");
    else
    {
        u32 mid = GetDist(graph, v1, v2);
        u32 result = std::min(dist_1[v1] + mid + GetDist(graph, v2, N), dist_1[v2] + mid + GetDist(graph, v1, N));

        printf("%u\n", result);
    }
}

std::vector<u32> Dijkstra(const std::vector< std::vector<Edge> >& graph, u32 s)
{
    std::vector<u32> dist(graph.size(), 0xFFFFFFFF);
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

u32 GetDist(const std::vector< std::vector<Edge> >& graph, u32 u, u32 v)
{
    u32 dist = 0xFFFFFFFF;
    bool* visited = new bool[graph.size()];
    memset(visited, false, graph.size() * sizeof(bool));
    constexpr auto min = [](const Edge& x, const Edge& y)->bool{ return x.w > y.w; };
    std::priority_queue<Edge, std::vector<Edge>, decltype(min)> que(min);

    que.push(std::move(Edge{u, 0}));

    while(!que.empty())
    {
        Edge edge = que.top();
        que.pop();

        if(visited[edge.v] == false)
        {
            visited[edge.v] = true;

            if(edge.v == v)
            {
                dist = edge.w;
                break;
            }

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