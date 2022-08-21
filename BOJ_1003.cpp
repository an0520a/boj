#include <cstdio>
#include <queue>
#include <vector>
#include <memory.h>

typedef unsigned long long u64;
typedef unsigned long u32;
typedef unsigned short u16;

std::vector<u32> TopologicalSort(std::vector< std::vector<u32> > out_graph);

int main()
{
    u64 T;

    for (size_t i = 0; i < T; i++)
    {
        u64 N, K;
        scanf(" %llu", &T);
        scanf(" %llu %llu", &N, &K);

        std::vector< std::vector<u32> > out_graph;
        out_graph.resize(N + 1);

        u32* build_time = new u32[N + 1];
        u32* total_build_time = new u32[N + 1];
        u32 max_time = 0;
        auto max = [](const u32& x, const u32& y)->u32{ return (x > y)? x : y; };

        for (size_t i = 1; i <= N; i++)
        {
            scanf(" %u", &build_time[i]);
        }

        for (size_t i = 0; i < K; i++)
        {
            u32 u, v;
            scanf(" %u %u", &u, &v);

            out_graph[u].push_back(v);
        }

        memcpy(total_build_time, build_time, (N + 1) * sizeof(u32));

        std::vector<u32> topological_sort_result;
        for (u32 i : topological_sort_result)
        {
            total_build_time[i] += build_time[i];
            max_time = max(max_time, total_build_time[i]);

            for (u32 j : out_graph[i])
            {
                total_build_time[j] += build_time[i];
            }
        }

        delete[] total_build_time;
        delete[] build_time;

        printf("%ul\n", max_time);
    }
    
    

}

std::vector<u32> TopologicalSort(std::vector< std::vector<u32> > out_graph)
{
    std::vector<u32> result;
    u32* indegree = new u32[out_graph.size()];
    memset(indegree, 0x00, out_graph.size() * sizeof(u32));

    for (u32 i = 1; i < out_graph.size(); i++)
    {
        for (u32 v : out_graph[i])
        {
            indegree[v]++;
        }
    }

    std::queue<u32> que;

    for (u32 i = 1; i < out_graph.size(); i++)
    {
        if(indegree[i] == 0) que.push(i), result.push_back(i);
    }

    while(que.empty() == false)
    {
        u32 v = que.back();
        que.pop();

        for (u32 i : out_graph[v])
        {
            indegree[i]--;
            if(indegree[i] == 0) que.push(i), result.push_back(i);
        }
    }

    delete[] indegree;

    return result;
}