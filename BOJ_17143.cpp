#include <cstdio>
#include <malloc.h>
#include <memory.h>
#include <queue>

typedef unsigned int u32;

typedef enum _dir
{
    up = 1,
    down,
    right,
    left
} dir;

typedef struct _shark
{
    u32 y;
    u32 x;
    u32 speed;
    dir to;
    u32 key;
} shark;

using namespace std;

int main()
{
    u32 R, C, M;
    u32 catchSize = 0;
    queue<shark> que;

    scanf(" %u %u %u", &R, &C, &M);

    u32 (*graph)[C] = (u32 (*)[C])calloc(R * C, sizeof(u32));
    u32* sharkSize = (u32 *)malloc((M + 1) * sizeof(u32));
    bool* live = (bool *)malloc((M + 1) * sizeof(bool));
    memset(live, true, (M + 1) * sizeof(bool));

    for (u32 i = 1; i <= M; i++)
    {
        u32 r, c, s, d, z;
        scanf(" %u %u %u %u %u", &r, &c, &s, &d, &z);

        que.push({r - 1, c - 1, s, dir(d), i});
        sharkSize[i] = z; 
        graph[r - 1][c - 1] = i;
    }

    for (u32 i = 0; i < C; i++)
    {
        u32 que_size = que.size();

        for (u32 j = 0; j < R; j++)
        {
            if(graph[j][i] != 0)
            {
                u32 k = graph[j][i];
                live[graph[j][i]] = false;
                catchSize += sharkSize[graph[j][i]];
                break;
            }
        }

        memset(graph, 0, R * C * sizeof(u32));

        for (u32 j = 0; j < que_size; j++)
        {
            shark shr = que.front();
            que.pop();

            if(live[shr.key] == true)
            {
                u32 dist = shr.speed;

                if(shr.to == up || shr.to == down)
                {
                    dist = dist % (2 * (R - 1));

                    if     (shr.to == up   && dist >= shr.y            ) shr.to = down, dist -= shr.y          , shr.y = 0;
                    else if(shr.to == down && dist >= ((R - 1) - shr.y)) shr.to = up  , dist -= (R - 1) - shr.y, shr.y = R - 1;

                    if     (shr.to == up   && dist >= shr.y            ) shr.to = down, dist -= shr.y          , shr.y = 0;
                    else if(shr.to == down && dist >= ((R - 1) - shr.y)) shr.to = up  , dist -= (R - 1) - shr.y, shr.y = R - 1;

                    if   (shr.to == up) shr.y -= dist;
                    else                shr.y += dist;
                }
                else
                {
                    dist = dist % (2 * (C - 1));

                    if     (shr.to == left  && dist >= shr.x            ) shr.to = right, dist -= shr.x          , shr.x = 0;
                    else if(shr.to == right && dist >= ((C - 1) - shr.x)) shr.to = left , dist -= (C - 1) - shr.x, shr.x = C - 1;

                    if     (shr.to == left  && dist >= shr.x            ) shr.to = right, dist -= shr.x          , shr.x = 0;
                    else if(shr.to == right && dist >= ((C - 1) - shr.x)) shr.to = left , dist -= (C - 1) - shr.x, shr.x = C - 1;

                    if   (shr.to == left) shr.x -= dist;
                    else                  shr.x += dist;
                }

                if(graph[shr.y][shr.x] == 0) graph[shr.y][shr.x] = shr.key, que.push(shr);
                else
                {
                    if(sharkSize[graph[shr.y][shr.x]] > sharkSize[shr.key])
                    {
                        live[shr.key] = false;
                    }
                    else
                    {
                        live[graph[shr.y][shr.x]] = false;
                        graph[shr.y][shr.x] = shr.key;

                        que.push(shr);
                    }
                }
            }
        }
    }

    printf("%u\n", catchSize);

    free(live);
    free(sharkSize);
    free(graph);
}