#include <stdio.h>
#include <vector>
#include <queue>

typedef unsigned int u32;

using namespace std;

int main()
{
    u32 N, M;
    u32* inDegree;
    queue<u32> que;

    scanf(" %u %u", &N, &M);

    vector< vector<u32> > vec;
    inDegree = new u32[N + 1]{ 0 };
    vec.resize(N + 1);

    for (u32 i = 0; i < M; i++)
    {
        u32 u, v;
        scanf(" %u %u", &u, &v);

        vec[u].push_back(v);
        inDegree[v]++;
    }

    for (u32 i = 1; i <= N; i++)
    {
        if(inDegree[i] == 0) que.push(i);
    }

    while(!que.empty())
    {
        u32 v = que.front();
        que.pop();

        printf("%u ", v);

        while(!vec[v].empty())
        {
            inDegree[vec[v].back()]--;
            
            if(inDegree[vec[v].back()] == 0)
            {
                que.push(vec[v].back());
            }

            vec[v].pop_back();
        }
    }

    delete[] inDegree;
}