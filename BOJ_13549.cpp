#include <stdio.h>
#include <deque>

typedef unsigned short u16;
typedef unsigned int u32;
typedef struct _entry
{
    u32 pos;
    u32 time;
} entry;

using namespace std;

u32 find(u32 x, u32 y);

int main()
{
    u32 N, M;
    scanf(" %u %u", &N, &M);

    printf("%u\n", find(N, M));
}

u32 find(u32 x, u32 y)
{
    bool visited[100001] = { false };

    deque<entry> deq;

    deq.push_back({x, 0});

    while (!deq.empty())
    {
        entry p = deq.front();
        deq.pop_front();

        if (p.pos == y) return p.time;

        if (p.pos <=  50000 && !visited[p.pos * 2]) visited[p.pos * 2] = true, deq.push_front({p.pos * 2, p.time   });
        if (p.pos !=      0 && !visited[p.pos - 1]) visited[p.pos - 1] = true, deq.push_back({p.pos - 1, p.time + 1});
        if (p.pos != 100000 && !visited[p.pos + 1]) visited[p.pos + 1] = true, deq.push_back({p.pos + 1, p.time + 1});
    }
}