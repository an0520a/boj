#include <iostream>
#include <vector>

typedef unsigned int u32;

typedef struct StructEdge
{
    u32 v;
    u32 w;
} Edge;

std::vector< std::vector<u32> > FloydWarshall(const std::vector< std::vector<Edge> >& graph);

int main()
{
    std::ios_base::sync_with_stdio(false);

    std::vector< std::vector<Edge> > graph;
    u32 n, m;

    std::cin >> n;
    std::cin >> m;

    graph.resize(n + 1);

    for (size_t i = 0; i < m; i++)
    {
        u32 u, v, w;

        std::cin >> u >> v >> w;

        graph[u].push_back({v, w});
    }

    auto cost_vec = FloydWarshall(graph);

    for (size_t i = 1; i < graph.size(); i++)
    {
        for (size_t j = 1; j < graph.size(); j++)
        {
            if(cost_vec[i][j] == 0x7FFFFFFF) std::cout << 0 << ' ';
            else                          std::cout << cost_vec[i][j] << ' ';
        }

        std::cout << '\n';
    }
}

std::vector< std::vector<u32> > FloydWarshall(const std::vector< std::vector<Edge> >& graph)
{
    std::vector< std::vector<u32> > cost_vec;

    cost_vec.resize(graph.size());
    for (size_t i = 1; i < graph.size(); i++)
    {
        cost_vec[i].resize(graph.size(), 0x7FFFFFFF);
    }

    for (size_t i = 1; i < graph.size(); i++)
    {
        cost_vec[i][i] = 0;
        
        for (size_t j = 0; j < graph[i].size(); j++)
        {
            cost_vec[i][graph[i][j].v] = std::min(cost_vec[i][graph[i][j].v], graph[i][j].w);
        }
    }

    for (size_t mid_v = 1; mid_v < graph.size(); mid_v++)
    {
        for (size_t src_v = 1; src_v < graph.size(); src_v++)
        {
            for (size_t dst_v = 1; dst_v < graph.size(); dst_v++)
            {
                if(src_v == dst_v)
                {
                    continue;
                }

                cost_vec[src_v][dst_v] = std::min(cost_vec[src_v][dst_v], cost_vec[src_v][mid_v] + cost_vec[mid_v][dst_v]);
            }
        }
    }

    return cost_vec;
}