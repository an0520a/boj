#include <stdio.h>
#include <queue>
#include <vector>

typedef unsigned int u32;

using namespace std;

vector<u32> BFS(const vector< vector<u32> >& vec);

int main()
{
    u32 N;
    vector< vector<u32> > vec;

    scanf(" %u", &N);
    
    vec.resize(N + 1);

    for (u32 i = 1; i < N; i++)
    {
        u32 u, v;
        scanf(" %u %u", &u, &v);
        
        vec[u].push_back(v);
        vec[v].push_back(u);
    }

    vector<u32> result = BFS(vec);

    for (u32 i = 2; i <= N; i++)
    {
        printf("%u\n", result[i]);
    }
}

vector<u32> BFS(const vector< vector<u32> >& vec)
{
    vector<u32> result(vec.size(), 0);
    queue<u32> que;

    que.push(1);
    result[1] = 1;

    while (!que.empty())
    {
        u32 vertex = que.front();
        que.pop();

        for (u32 i = 0; i < vec[vertex].size(); i++)
        {
            const u32& next = vec[vertex][i];

            if(result[next] == 0)
            {
                result[next] = vertex;
                que.push(next);
            }
        }
    }

    return result;
}