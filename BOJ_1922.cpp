#include <cstdio>
#include <algorithm>

typedef unsigned int u32;

typedef struct _edge
{
    u32 u;
    u32 v;
    u32 w;
} edge;

using namespace std;

u32 getRoot(u32* parent, u32 x);

int main()
{
    u32 N, M;
    u32 result = 0;
    u32* parent;
    edge* edge_arr;

    scanf(" %u", &N);
    scanf(" %u", &M);

    edge_arr = new edge[M];
    parent = new u32[N + 1];

    for (u32 i = 0; i < M; i++) scanf(" %u %u %u", &edge_arr[i].u, &edge_arr[i].v, &edge_arr[i].w);
    for (u32 i = 1; i <= N; i++) parent[i] = i;

    sort(edge_arr, edge_arr + M, [](const edge& x, const edge& y)->bool{ return x.w < y.w; });

    for (u32 i = 0; i < M; i++)
    {
        if(getRoot(parent, edge_arr[i].u) != getRoot(parent, edge_arr[i].v))
        {
            parent[getRoot(parent, edge_arr[i].v)] = getRoot(parent, edge_arr[i].u);
            result += edge_arr[i].w;
        }
    }

    printf("%u\n", result);

    delete[] parent;
    delete[] edge_arr;
}

u32 getRoot(u32* parent, u32 x)
{
    if(parent[x] == x) return x;
    else return parent[x] = getRoot(parent, parent[x]);
}