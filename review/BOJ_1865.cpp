#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>

typedef unsigned int u32;

typedef struct StructEdge
{
    u32 v;
    int w;
} Edge;

bool CheckNegativeCycle(const std::vector< std::vector<Edge> >& graph);

int main()
{
    std::ios_base::sync_with_stdio(false);

    size_t TC;
    size_t N, M, W;
    
    std::cin >> TC;

    for (size_t i = 0; i < TC; i++)
    {
        std::vector <std::vector<Edge> > graph;

        std::cin >> N >> M >> W;

        graph.resize(N + 1);

        for (size_t i = 0; i < M; i++)
        {
            u32 S, E;
            int T;

            std::cin >> S >> E >> T;

            graph[S].push_back({E, T});
            graph[E].push_back({S, T});
        }

        for (size_t i = 0; i < W; i++)
        {
            u32 S, E;
            int T;

            std::cin >> S >> E >> T;

            graph[S].push_back({E, -T});
        }

        std::cout << (CheckNegativeCycle(graph)? "YES" : "NO") << "\n";
    }
}

bool CheckNegativeCycle(const std::vector< std::vector<Edge> >& graph)
{
    int* dist_arr = new int[graph.size()];
    memset(dist_arr, 0, graph.size() * sizeof(int));
    std::queue<Edge> que;

    for (u32 i = 1; i < graph.size(); i++) que.push({i, 0});
    
    for (size_t i = 0; i < graph.size() - 1; i++)
    {
        const size_t que_size = que.size();

        for (size_t j = 0; j < que_size; j++)
        {
            const Edge edge = que.front();
            que.pop();

            for (Edge next_edge : graph[edge.v])
            {
                next_edge.w += edge.w;

                if(next_edge.w < dist_arr[next_edge.v])
                {
                    dist_arr[next_edge.v] = next_edge.w;

                    que.push(next_edge);
                }
            }
        }
    }

    while(!que.empty())
    {
        const Edge edge = que.front();
        que.pop();

        for (Edge next_edge : graph[edge.v])
        {
            next_edge.w += edge.w;

            if(next_edge.w < dist_arr[next_edge.v])
            {
                return true;
            }
        }
    }

    return false;
}