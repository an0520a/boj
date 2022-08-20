#include <stdio.h>
#include <queue>
#include <algorithm>

typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct _entry
{
    u32 M;
    u32 V;
} entry;

using namespace std;

int main()
{
    u32 N, K;
    u64 result = 0;
    entry* jewers;
    u32* bags;
    auto sort_cmp = [](const entry& x, const entry& y)->bool{ return x.M < y.M; };
    auto heap_cmp = [](const entry& x, const entry& y)->bool{ return ((x.V != y.V)? (x.V < y.V) : (x.M > y.M)); };
    priority_queue<entry, vector<entry>, decltype(heap_cmp)> que(heap_cmp);

    scanf(" %u %u", &N, &K);

    jewers = new entry[N];
    bags = new u32[K];

    for (u32 i = 0; i < N; i++)
    {
        scanf(" %u %u", &jewers[i].M, &jewers[i].V);
    }

    for (u32 i = 0; i < K; i++)
    {
        scanf(" %u", bags + i);
    }

    sort(bags, bags + K);
    sort(jewers, jewers + N, sort_cmp);

    u32 j = 0;
    for (u32 i = 0; i < K; i++)
    {
        u32 bag = bags[i];

        for (; j < N && jewers[j].M <= bag; j++)
        {
            que.push(jewers[j]);
        }

        if (!que.empty())
        {
            result += que.top().V;
            que.pop();
        }
    }

    printf("%llu\n", result);

    delete[] bags;
    delete[] jewers;
}