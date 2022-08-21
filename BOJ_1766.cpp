#include <cstdio>
#include <vector>
#include <queue>
#include <memory.h>

typedef unsigned int u32;

using namespace std;

void topologicalSort(const vector< vector<u32> >& vec, const u32* inDegree);

int main()
{
    u32 N, M;
    vector< vector<u32> > vec;
    u32* inDegree;

    scanf(" %u %u", &N, &M);

    vec.resize(N + 1);
    inDegree = new u32[N + 1]{ 0 };

    for (u32 i = 0; i < M; i++)
    {
        u32 u, v;
        
        scanf(" %u %u", &u, &v);

        vec[u].push_back(v);
        inDegree[v]++;
    }

    topologicalSort(vec, inDegree);

    delete[] inDegree;
}

void topologicalSort(const vector< vector<u32> >& vec, const u32* inDegree)
{
    priority_queue<u32, vector<u32>, greater<u32> > que;
    u32* localInDegree = new u32[vec.size()];
    memcpy(localInDegree, inDegree, vec.size() * sizeof(u32));

    for (u32 i = 1; i < vec.size(); i++) if(localInDegree[i] == 0) que.push(i);

    while(!que.empty())
    {
        u32 vertex = que.top();
        que.pop();

        printf("%u ", vertex);

        for (u32 i = 0; i < vec[vertex].size(); i++)
        {
            localInDegree[vec[vertex][i]]--;

            if(localInDegree[vec[vertex][i]] == 0) que.push(vec[vertex][i]);
        }
    }

    printf("\n");

    delete[] localInDegree;
}