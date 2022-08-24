#include <cstdio>
#include <deque>
#include <memory.h>

typedef unsigned int u32;

typedef struct StructEntry
{
    u32 vertex;
    u32 time;
} Entry;

int main()
{
    u32 N, K;
    constexpr u32 kMapSize = 100001;
    u32 time[kMapSize]; memset(time, 0xFF, sizeof(time));
    std::deque<Entry> deq;


    scanf(" %u %u", &N, &K);

    time[N] = 0;
    deq.push_front({N, 0});

    while(!deq.empty())
    {
        Entry entry = deq.front();
        deq.pop_front();

        if (entry.vertex == K) break;

        if (entry.vertex * 2 < kMapSize && entry.time < time[entry.vertex * 2]) time[entry.vertex * 2] = entry.time, deq.push_front({entry.vertex * 2, entry.time});
        if (entry.vertex != 0 && entry.time + 1 < time[entry.vertex - 1]) time[entry.vertex - 1] = entry.time + 1, deq.push_back({entry.vertex - 1, entry.time + 1});
        if (entry.vertex + 1 != kMapSize && entry.time + 1 < time[entry.vertex + 1]) time[entry.vertex + 1] = entry.time + 1, deq.push_back({entry.vertex + 1, entry.time + 1});
    }

    printf("%u\n", time[K]);
}