#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>

typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct _entry
{
    u32 vertex;
    u32 weight;
} entry;

using namespace std;

pair<u32, u32> getPairMinWeight(const vector< vector<entry> > vec, const u32& u, const u32& v1, const u32& v2);
u32 getMinWeight(const vector< vector<entry> > vec, const u32& u, const u32& v);

int main()
{
    u32 N, E;
    u32 v1, v2;
    u64 holdVAL;
    u64 case1, case2, case3, case4;
    u64 min = 0xFFFFFFFF;
    pair<u32, u32> fromStr, toEnd;
    vector< vector<entry> > vec;

    scanf(" %u %u", &N, &E);

    vec.resize(N + 1);

    for (u32 i = 0; i < E; i++)
    {
        u32 u, v, w;
        scanf(" %u %u %u", &u, &v, &w);

        vec[u].push_back({v, w});
        vec[v].push_back({u, w});
    }

    scanf(" %u %u", &v1, &v2);

    fromStr = getPairMinWeight(vec, 1, v1, v2);
    toEnd = getPairMinWeight(vec, N, v1, v2);
    holdVAL = getMinWeight(vec, v1, v2);

    case1 = fromStr.first + holdVAL * 2 + toEnd.first;
    case2 = fromStr.first + holdVAL + toEnd.second;
    case3 = fromStr.second + holdVAL + toEnd.first;
    case4 = fromStr.second + holdVAL * 2 + toEnd.second;

    min = (min < case1)? min : case1;
    min = (min < case2)? min : case2;
    min = (min < case3)? min : case3;
    min = (min < case4)? min : case4;

    if(min != 0xFFFFFFFF) printf("%llu\n", min);
    else printf("-1\n");

    return 0;
}

pair<u32, u32> getPairMinWeight(const vector< vector<entry> > vec, const u32& u, const u32& v1, const u32& v2)
{
    u32* dist = new u32[vec.size()];
    memset(dist, 0xFF, vec.size() * sizeof(u32));
    pair<u32, u32> result;

    auto cmp = [](const entry& x, const entry& y)->bool{ return x.vertex > y.vertex; };
    priority_queue<entry, vector<entry>, decltype(cmp)> que(cmp);

    que.push({u, 0});
    dist[u] = 0;

    while(!que.empty())
    {
        entry tmp = que.top();
        que.pop();

        for (u32 i = 0; i < vec[tmp.vertex].size(); i++)
        {
            const entry& next = vec[tmp.vertex][i];

            if (tmp.weight + next.weight <= dist[next.vertex])
            {
                dist[next.vertex] = tmp.weight + next.weight;
                que.push({next.vertex, dist[next.vertex]});
            }
        }
    }

    result = {dist[v1], dist[v2]};

    delete[] dist;

    return result;
}

u32 getMinWeight(const vector< vector<entry> > vec, const u32& u, const u32& v)
{
    u32* dist = new u32[vec.size()];
    memset(dist, 0xFF, vec.size() * sizeof(u32));
    u32 result;

    auto cmp = [](const entry& x, const entry& y)->bool{ return x.vertex > y.vertex; };
    priority_queue<entry, vector<entry>, decltype(cmp)> que(cmp);

    que.push({u, 0});
    dist[u] = 0;

    while(!que.empty())
    {
        entry tmp = que.top();
        que.pop();

        for (u32 i = 0; i < vec[tmp.vertex].size(); i++)
        {
            const entry& next = vec[tmp.vertex][i];

            if (tmp.weight + next.weight < dist[next.vertex])
            {
                dist[next.vertex] = tmp.weight + next.weight;
                que.push({next.vertex, dist[next.vertex]});
            }
        }
    }

    result = dist[v];

    delete[] dist;

    return result;
}