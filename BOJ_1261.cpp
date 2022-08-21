#include <cstdio>
#include <malloc.h>
#include <deque>

typedef unsigned int u32;

using namespace std;

typedef struct _point
{
    u32 y;
    u32 x;
} point;

typedef struct _entry
{
    point p;
    u32 w;
} entry;

int main()
{
    u32 N, M;

    scanf(" %u %u", &M, &N);

    char (*map)[M + 1] = (char (*)[M + 1])malloc(N * (M + 1) * sizeof(char));
    bool (*visited)[M] = (bool (*)[M])calloc(N * M, sizeof(bool));

    for (u32 i = 0; i < N; i++) scanf(" %s", map[i]);

    deque<entry> deq;

    deq.push_back({{0, 0}, 0});

    while(deq.front().p.y != N - 1 || deq.front().p.x != M - 1)
    {
        entry ent = deq.front();
        const point& p = ent.p;

        deq.pop_front();

        if(visited[p.y][p.x]) continue;
        else                  visited[p.y][p.x] = true;

        if(p.y != 0 && !visited[p.y - 1][p.x])
        {
            if(map[p.y - 1][p.x] == '0') deq.push_front({{p.y - 1, p.x}, ent.w});
            else                         deq.push_back({{p.y - 1, p.x}, ent.w + 1});
        }

        if(p.y != N - 1 && !visited[p.y + 1][p.x])
        {
            if(map[p.y + 1][p.x] == '0') deq.push_front({{p.y + 1, p.x}, ent.w});
            else                         deq.push_back({{p.y + 1, p.x}, ent.w + 1});
        }

        if(p.x != 0 && !visited[p.y][p.x - 1])
        {
            if(map[p.y][p.x - 1] == '0') deq.push_front({{p.y, p.x - 1}, ent.w});
            else                         deq.push_back({{p.y, p.x - 1}, ent.w + 1});
        }

        if(p.x != M - 1 && !visited[p.y][p.x + 1])
        {
            if(map[p.y][p.x + 1] == '0') deq.push_front({{p.y, p.x + 1}, ent.w});
            else                         deq.push_back({{p.y, p.x + 1}, ent.w + 1});
        }
    }

    printf("%u\n", deq.front().w);

    free(visited);
    free(map);
}