#include <stdio.h>
#include <vector>
#include <queue>

typedef unsigned int u32;

using namespace std;

u32 getMaxTime(const vector< vector<u32> > graph, u32* time, const u32& dst);

int main()
{
    u32 T;

    scanf(" %u", &T);

    while(T--)
    {
        u32 N, K;
        u32* time;
        u32 dst;
        vector< vector<u32> > graph;

        scanf(" %u %u", &N, &K);

        time = new u32[N + 1];
        graph.resize(N + 1);

        for (u32 i = 1; i <= N; i++)
        {
            scanf(" %u", time + i);
        }

        for (u32 i = 0; i < K; i++)
        {
            u32 u, v;
            scanf(" %u %u", &u, &v);

            graph[u].push_back(v);
        }

        scanf(" %u", &dst);
        
        printf("%u\n", getMaxTime(graph, time, dst));

        delete[] time;
    }
}

u32 getMaxTime(const vector< vector<u32> > graph, u32* time, const u32& dst)
{
    vector< vector<u32> > reverse;
    queue<u32> que;
    u32 dst_result;
    u32* result;
    u32* inDegree;

    result = new u32[graph.size()]{ 0 };
    inDegree = new u32[graph.size()]{ 0 };
    reverse.resize(graph.size());

    for (u32 i = 1; i < graph.size(); i++)
    {
        for (u32 j = 0; j < graph[i].size(); j++)
        {
            reverse[graph[i][j]].push_back(i);
        }
    }

    for (u32 i = 1; i < graph.size(); i++)
    {
        if((inDegree[i] = reverse[i].size()) == 0) que.push(i);
    }

    while(!que.empty())
    {
        u32 v = que.front();
        u32 max = 0;
        que.pop();

        for (u32 i = 0; i < reverse[v].size(); i++)
        {
            max = (result[reverse[v][i]] > max)? result[reverse[v][i]] : max;
        }

        result[v] = time[v] + max;

        for (u32 i = 0; i < graph[v].size(); i++)
        {
            inDegree[graph[v][i]]--;
            if (inDegree[graph[v][i]] == 0) que.push(graph[v][i]);
        }
    }

    dst_result = result[dst];

    delete[] result;
    delete[] inDegree;

    return dst_result;
}