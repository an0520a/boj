#include <cstdio>
#include <vector>
#include <queue>
#include <memory.h>

typedef unsigned int u32;

typedef struct _entry
{
    u32 v;
    u32 w;
} entry;

using namespace std;

u32 MST_weight(const vector< vector<entry> >& vec);

int main()
{
    u32 N, M;
    vector< vector<entry> > vec;

    scanf(" %u %u", &N, &M);

    vec.resize(N + 1);

    for (u32 i = 0; i < M; i++)
    {
        u32 u, v, w;
        
        scanf(" %u %u %u", &u, &v, &w);

        vec[u].push_back({v, w});
        vec[v].push_back({u, w});
    }

    printf("%u\n", MST_weight(vec));
}

u32 MST_weight(const vector< vector<entry> >& vec)
{
    bool* visited = new bool[vec.size()]{ false };
    auto cmp = [](const entry& x, const entry& y)->bool{ return x.w > y.w; };
    priority_queue<entry, vector<entry>, decltype(cmp)> que(cmp);
    u32 weight_sum = 0;
    u32 max = 0;

    visited[1] = true;
    for (u32 i = 0; i < vec[1].size(); i++) que.push({vec[1][i]});

    while(!que.empty())
    {
        entry v = que.top();
        que.pop();

        if(visited[v.v] == false)
        {
            visited[v.v] = true;
            weight_sum += v.w;
            max = (v.w > max)? v.w : max;

            for (u32 i = 0; i < vec[v.v].size(); i++)
            {
                if(visited[vec[v.v][i].v] == false) que.push(vec[v.v][i]);
            }
        }
    }

    delete[] visited;

    return weight_sum - max;
}