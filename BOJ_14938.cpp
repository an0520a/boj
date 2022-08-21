#include <stdio.h>
#include <memory.h>
#include <queue>
#include <vector>

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct _entry
{
    u32 vertex;
    u32 weight;
} entry;

using namespace std;

u32 getMaxItem(const vector< vector<entry> >& vec, u32* itemArr, u32 m);

int main()
{
    u32 n, m, r;
    u32 *itemArr;
    vector< vector<entry> > vec;
    
    scanf(" %u %u %u", &n, &m, &r);

    vec.resize(n + 1);
    itemArr = new u32[n + 1];

    for (u32 i = 1; i <= n; i++) scanf(" %u", itemArr + i);

    for (u32 i = 0; i < r; i++)
    {
        u32 u, v, w;
        scanf(" %u %u %u", &u, &v, &w);

        vec[u].push_back({v, w});
        vec[v].push_back({u, w});
    }

    printf("%u\n", getMaxItem(vec, itemArr, m));

    delete[] itemArr;
}

u32 getMaxItem(const vector< vector<entry> >& vec, u32* itemArr, u32 m)
{
    u32 max = 0;
    u32* dist = new u32[vec.size()];
    auto cmp = [](const entry& a, const entry& b)->bool{ return a.weight > b.weight; };
    priority_queue<entry, vector<entry>, decltype(cmp)> que(cmp);

    for (u32 i = 1; i < vec.size(); i++)
    {
        u32 sum = 0;
        memset(dist, 0xFF, vec.size() * sizeof(u32));

        que.push({i, 0});
        dist[i] = 0;
        
        while(!que.empty())
        {
            entry tmp = que.top();
            que.pop();

            for (u32 i = 0; i < vec[tmp.vertex].size(); i++)
            {
                if (vec[tmp.vertex][i].weight + tmp.weight < dist[vec[tmp.vertex][i].vertex])
                {
                    dist[vec[tmp.vertex][i].vertex] = vec[tmp.vertex][i].weight + tmp.weight;
                    que.push({vec[tmp.vertex][i].vertex, dist[vec[tmp.vertex][i].vertex]});
                }
            }
        }

        for (u32 j = 1; j < vec.size(); j++)
        {
            if (dist[j] <= m) sum += itemArr[j];
        }
        max = (sum > max)? sum : max;

        /*
        printf("%u\n", i);
        for (u32 j = 1; j < vec.size(); j++)
        {
            printf("%u(%u) ", dist[j], dist[j] <= m);
        }
        printf("\n-------%02u--------\n", sum);
        */

    }

    delete[] dist;

    return max;
}