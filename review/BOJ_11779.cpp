#include <iostream>
#include <vector>
#include <memory.h>
#include <queue>
#include <stack>

typedef unsigned int u32;

typedef struct StructEdge
{
    u32 v;
    u32 w;
} Edge;


int main()
{
    constexpr auto edge_comp = [](const Edge& __x, const Edge& __y)->bool{ return __x.w > __y.w; };
    u32 n, m;
    u32 src, dst;
    std::vector< std::vector<Edge> > graph;
    std::priority_queue<Edge, std::vector<Edge>, decltype(edge_comp)> que(edge_comp);
    std::vector<u32> dist_vec;
    std::vector<u32> prev_vertex_vec;

    std::ios_base::sync_with_stdio(false);

    std::cin >> n;
    std::cin >> m;

    graph.resize(n + 1);
    dist_vec.resize(n + 1, 0x7FFFFFFF);
    prev_vertex_vec.resize(n + 1, 0);

    for (u32 i = 0; i < m; i++)
    {
        u32 u, v, w;

        std::cin >> u >> v >> w;

        graph[u].push_back({v, w});
    }

    std::cin >> src >>dst;

    que.push({src, 0});
    dist_vec[src] = 0;


    while(!que.empty())
    {
        Edge edge = que.top();
        if(edge.v == dst) break;
        que.pop();


        for (Edge next_edge : graph[edge.v])
        {
            next_edge.w += edge.w;

            if (next_edge.w < dist_vec[next_edge.v])
            {
                prev_vertex_vec[next_edge.v] = edge.v;
                dist_vec[next_edge.v] = next_edge.w;


                que.push(next_edge);
            }
        }
    }

    u32 vertex = dst;
    std::stack<u32> stk;

    do
    {
        stk.push(vertex);
        vertex = prev_vertex_vec[vertex];
    } while(stk.top() != src);

    std::cout << dist_vec[dst] << "\n"
              << stk.size() << "\n";
    
    while(!stk.empty())
    {
        std::cout << stk.top() << ' ';
        stk.pop();
    }

    std::cout << std::endl;
}

