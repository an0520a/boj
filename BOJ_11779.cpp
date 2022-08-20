#include <stdio.h>
#include <memory.h>
#include <queue>
#include <stack>
#include <vector>

typedef unsigned int u32;
typedef struct  _entry
{
    u32 vertex;
    u32 weight;
} entry;

using namespace std;

void getMinPath(const vector< vector<entry> > vec, u32 org, u32 dst);

int main()
{
    u32 n, m, org, dst;
    scanf(" %u", &n);
    scanf(" %u", &m);

    vector< vector<entry> > vec;
    vec.resize(n + 1);

    for (u32 i = 0; i < m; i++)
    {
        u32 u, v, w;
        scanf(" %u %u %u", &u, &v, &w);

        vec[u].push_back({v, w});
    }

    scanf(" %u %u", &org, &dst);

    getMinPath(vec, org, dst);
}

void getMinPath(const vector< vector<entry> > vec, u32 org, u32 dst)
{
    u32* dist = new u32[vec.size() + 1];
    u32* priV = new u32[vec.size() + 1];
    memset(dist, 0xFF, (vec.size() + 1) * sizeof(u32));
    auto cmp = [](const entry& x, const entry& y)->bool{ return x.weight > y.weight; };

    priority_queue<entry, vector<entry>, decltype(cmp)> que(cmp);
    que.push({org, 0});
    dist[org] = 0;

    while(!que.empty())
    {
        entry tmp = que.top();
        que.pop();

        if (tmp.vertex == dst) break;

        for (u32 i = 0; i < vec[tmp.vertex].size(); i++)
        {
            if (tmp.weight + vec[tmp.vertex][i].weight < dist[vec[tmp.vertex][i].vertex])
            {
                dist[vec[tmp.vertex][i].vertex] = tmp.weight + vec[tmp.vertex][i].weight;
                que.push({vec[tmp.vertex][i].vertex, dist[vec[tmp.vertex][i].vertex]});
                priV[vec[tmp.vertex][i].vertex] = tmp.vertex;
            }
        }
    }

    u32 tmp = dst;
    stack<u32> path;

    while (true)
    {
        path.push(tmp);
        
        if(tmp == org) break;

        tmp = priV[tmp];
    }

    printf("%u \n", dist[dst]);
    printf("%lu \n", path.size());
    while(!path.empty())
    {
        printf("%u ", path.top());
        path.pop();
    }

    delete[] dist;
    delete[] priV;
}