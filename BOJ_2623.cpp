#include <cstdio>
#include <malloc.h>
#include <queue>
#include <vector>

typedef unsigned int u32;

using namespace std;

int main()
{
    u32 N, M;
    vector< vector<u32> > vec;
    vector<u32> result;
    queue<u32> que;
    u32* inDegree;

    scanf(" %u %u", &N, &M);

    vec.resize(N + 1);
    result.reserve(N);
    inDegree = (u32 *)calloc(N + 1, sizeof(u32));
    bool (*tmp_graph)[N + 1] = (bool (*)[N + 1])calloc((N + 1) * (N + 1), sizeof(bool));

    for (u32 i = 0; i < M; i++)
    {
        u32 K, u;

        scanf(" %u", &K);

        scanf(" %u", &u);

        for (u32 j = 1; j < K; j++)
        {
            u32 v;
            scanf(" %u", &v);

            if (tmp_graph[u][v] == false) tmp_graph[u][v] = true, inDegree[v]++, vec[u].push_back(v);

            u = v;
        }
    }
    free (tmp_graph);

    for (u32 i = 1; i <= N; i++) if(inDegree[i] == 0) que.push(i), result.push_back(i);

    while(!que.empty())
    {
        u32 v = que.front();
        que.pop();

        for (u32 i = 0; i < vec[v].size(); i++) if (--inDegree[vec[v][i]] == 0) que.push(vec[v][i]), result.push_back(vec[v][i]);

        vec[v].clear();
    }

    if (result.size() == N) for (u32 i = 0; i < result.size(); i++) printf("%u\n", result[i]);
    else                                                            printf("0\n");

    free (inDegree);
}