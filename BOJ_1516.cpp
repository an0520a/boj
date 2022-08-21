#include <cstdio>
#include <queue>
#include <vector>

typedef unsigned int u32;

using namespace std;

int main()
{
    u32 N;
    vector< vector<u32> > inGraph;
    vector< vector<u32> > outGraph;
    queue<u32> que;
    u32* time;
    u32* result;
    u32* inDegree;

    scanf(" %u", &N);

    inGraph.resize(N + 1);
    outGraph.resize(N + 1);
    time = new u32[N + 1];
    inDegree = new u32[N + 1];
    result = new u32[N + 1]{ 0 };

    for (u32 i = 1; i <= N; i++)
    {
        scanf(" %u", time + i);

        u32 vertex;
        scanf(" %u", &vertex);

        while(vertex != -1)
        {
            inGraph[i].push_back(vertex);
            inDegree[i]++;
            scanf(" %u", &vertex);
        }
    }

    for (u32 i = 1; i <= N; i++)
    { 
        for (u32 j = 0; j < inGraph[i].size(); j++)
        {
            outGraph[inGraph[i][j]].push_back(i);
        }
    }

    for (u32 i = 1; i <= N; i++) if(inDegree[i] == 0) que.push(i), result[i] = time[i];

    while(!que.empty())
    {
        u32 v = que.front();
        que.pop();

        for (u32 i = 0; i < outGraph[v].size(); i++)
        {
            if(inDegree[outGraph[v][i]] == 1) que.push(outGraph[v][i]);
            inDegree[outGraph[v][i]]--;

            result[outGraph[v][i]] = (result[outGraph[v][i]] > result[v] + time[outGraph[v][i]])? result[outGraph[v][i]] : result[v] + time[outGraph[v][i]];
        }
    }

    for (u32 i = 1; i <= N; i++) printf("%u\n", result[i]);

    delete[] result;
    delete[] inDegree;
    delete[] time;
}