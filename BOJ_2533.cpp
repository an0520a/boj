#include <cstdio>
#include <vector>

typedef unsigned int u32;

using namespace std;

u32 DFS(const vector< vector<u32> >& graph);
u32 DFS_cmp(u32* memo, bool* calculated, const vector< vector<u32> >& graph, u32 idx);

int main()
{
    u32 N;
    u32 root;
    vector< vector<u32> > graph;

    scanf(" %u", &N);

    graph.resize(N + 1);

    for (u32 i = 1; i < N; i++)
    {
        u32 u, v;
        
        scanf(" %u %u", &u, &v);

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    printf("%u\n", DFS(graph));
}

u32 DFS(const vector< vector<u32> >& graph)
{
    u32 result;
    u32* memo = new u32[graph.size()]{ 0 };
    bool* calculated = new bool[graph.size()]{ false };

    result = DFS_cmp(memo, calculated, graph, 1);
    delete[] memo;
    delete[] calculated;
    
    return result;
}

u32 DFS_cmp(u32* memo, bool* calculated, const vector< vector<u32> >& graph, u32 idx)
{
    if(calculated[idx]) return memo[idx];
    u32 resultB = 1;
    u32 resultW = 0;
    calculated[idx] = true;

    for (u32 i = 0; i < graph[idx].size(); i++)
    {
        if(!calculated[graph[idx][i]])
        {
            resultB += DFS_cmp(memo, calculated, graph, graph[idx][i]);
            resultW++;

            for (u32 j = 0; j < graph[graph[idx][i]].size(); j++)
            {
                resultW += DFS_cmp(memo, calculated, graph, graph[graph[idx][i]][j]);
            }
        }

    }

    return memo[idx] = (resultB < resultW)? resultB : resultW;
}