#include <cstdio>
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
    u32 N, M;
    u32 src_city, dst_city;
    std::vector< std::vector<Edge> > graph;

    scanf(" %u", &N);
    scanf(" %u", &M);

    graph.resize(N + 1);

    for (size_t i = 0; i < M; i++)
    {
        u32 u, v, w;

        scanf(" %u %u %u", &u, &v, &w);

        graph[u].push_back({v, w});
    }

    scanf(" %u %u", &src_city, &dst_city);

    std::vector<u32> shortest_length_vec = Dijkstra(graph, src_city);

    printf("%u\n", shortest_length_vec[dst_city]);
}

std::vector<u32> Dijkstra(const std::vector< std::vector<Edge> >& graph, const u32& start_vertex)
{
    std::vector<u32> shortest_length_vec(graph.size(), 0);
    auto edge_comp = [](const Edge& x, const Edge& y)->bool{ return x.w > y.w; };
    std::priority_queue<Edge, std::vector<Edge>, decltype(edge_comp)> que(edge_comp);
    bool* visited = new bool[graph.size()];
    memset(visited, false, graph.size() * sizeof(bool));

    que.push({start_vertex, 0});

    while(!que.empty())
    {
        Edge edge = que.top();
        que.pop();

        if(visited[edge.v] == false)
        {
            visited[edge.v] = true;
            shortest_length_vec[edge.v] = edge.w;
            
            for (const Edge& next_edge : graph[edge.v])
            {
                if(visited[next_edge.v] == false)
                {
                    que.push({next_edge.v, edge.w + next_edge.w});
                }
            }
        }
    }

    delete[] visited;

    return shortest_length_vec;
}