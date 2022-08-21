#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#include <memory.h>

typedef unsigned int u32;
typedef unsigned long long u64;
typedef struct _point
{
    int x;
    int y;
    int z;
} point;
typedef struct _entry
{
    u32 ord;
    int num;
} entry;
typedef struct _edge
{
    u32 u;
    u32 v;
    u32 w;
} edge;

using namespace std;

u32 getRoot(u32* parent, u32 x)
{
    if(x == parent[x]) return x;
    else               return parent[x] = getRoot(parent, parent[x]);
}

int main()
{
    u32 N;
    u32 sum = 0;
    u32 count = 0;
    u32* parent;
    point* p_arr;
    entry *x_arr, *y_arr, *z_arr;
    auto edge_cmp = [](const edge& x, const edge& y)->bool{ return x.w > y.w; };
    auto abs_sub = [](const int& x, const int& y)->u32{ return (x > y)? x - y : y - x; };
    priority_queue<edge, vector<edge>, decltype(edge_cmp)> que(edge_cmp);

    scanf(" %u", &N);

    x_arr = new entry[N];
    y_arr = new entry[N];
    z_arr = new entry[N];
    parent = new u32[N];

    for (u32 i = 0; i < N; i++)
    {
        int x, y, z;
        scanf(" %d %d %d", &x, &y, &z);

        x_arr[i] = { i, x };
        y_arr[i] = { i, y };
        z_arr[i] = { i, z };
        parent[i] = i;
    }

    sort(x_arr, x_arr + N, [](const entry& x, const entry& y)->bool{ return x.num < y.num; });
    sort(y_arr, y_arr + N, [](const entry& x, const entry& y)->bool{ return x.num < y.num; });
    sort(z_arr, z_arr + N, [](const entry& x, const entry& y)->bool{ return x.num < y.num; });

    for (u32 i = 0; i < N - 1; i++)
    {
        que.push({x_arr[i].ord, x_arr[i + 1].ord, abs_sub(x_arr[i].num, x_arr[i + 1].num)});
        que.push({y_arr[i].ord, y_arr[i + 1].ord, abs_sub(y_arr[i].num, y_arr[i + 1].num)});
        que.push({z_arr[i].ord, z_arr[i + 1].ord, abs_sub(z_arr[i].num, z_arr[i + 1].num)});
    }

    while(!que.empty() && count != N - 1)
    {
        edge e = que.top();
        que.pop();
        u32 u_root = getRoot(parent, e.u);
        u32 v_root = getRoot(parent, e.v);

        if(u_root != v_root)
        {
            parent[u_root] = v_root;
            sum += e.w;
            count++;
        }
    }

    printf("%u\n", sum);

    delete[] parent;
    delete[] z_arr;
    delete[] y_arr;
    delete[] x_arr;
}
