#include <cstdio>
#include <queue>
#include <malloc.h>
#include <memory.h>

typedef unsigned int u32;

typedef struct _point
{
    u32 y;
    u32 x;
} point;

using namespace std;

int main()
{
    u32 N, M;
    u32* map;
    bool* used;
    queue<point> workQue;
    queue<point> que;

    scanf(" %u %u", &N, &M);

    u32 (*graph)[M] = (u32 (*)[M])malloc(N * M * sizeof(u32));
    char (*result)[M + 1] = (char (*)[M + 1])malloc(N * (M + 1) * sizeof(char));
    map = new u32[(N * M) / 2 + 5]{ 0 };
    used = new bool[(N * M) / 2 + 5]{ true, true, false };
    for (u32 i = 0; i < N; i++)
    {
        scanf(" %s", result[i]);
        result[i][M] = '\n';

        for (u32 j = 0; j < M; j++)
        {
            graph[i][j] = result[i][j] - '0';
            if(graph[i][j] != 0) workQue.push({i, j});
        }
    }
    result[N - 1][M] = '\0';

    u32 preKey = 3;
    for (u32 i = 0; i < N; i++)
    {
        for (u32 j = 0; j < M; j++)
        {
            if(graph[i][j] == 0)
            {
                que.push({i, j});
                graph[i][j] = preKey;
                map[preKey]++;

                while(!que.empty())
                {
                    point p = que.front();
                    que.pop();

                    if(p.y != 0     && graph[p.y - 1][p.x] == 0) graph[p.y - 1][p.x] = preKey, map[preKey]++, que.push({p.y - 1, p.x});
                    if(p.x != 0     && graph[p.y][p.x - 1] == 0) graph[p.y][p.x - 1] = preKey, map[preKey]++, que.push({p.y, p.x - 1});
                    if(p.y != N - 1 && graph[p.y + 1][p.x] == 0) graph[p.y + 1][p.x] = preKey, map[preKey]++, que.push({p.y + 1, p.x});
                    if(p.x != M - 1 && graph[p.y][p.x + 1] == 0) graph[p.y][p.x + 1] = preKey, map[preKey]++, que.push({p.y, p.x + 1});
                }

                map[preKey] = map[preKey] % 10;
                preKey++;
            }
        }
    }

    while(!workQue.empty())
    {
        point p = workQue.front();
        workQue.pop();
        u32 sum = 1;
        u32 a, b, c, d;
        a = b = c = d = 2;

        if(p.y != 0     && !used[graph[p.y - 1][p.x]]) a = graph[p.y - 1][p.x], used[graph[p.y - 1][p.x]] = true, sum += map[graph[p.y - 1][p.x]];
        if(p.x != 0     && !used[graph[p.y][p.x - 1]]) b = graph[p.y][p.x - 1], used[graph[p.y][p.x - 1]] = true, sum += map[graph[p.y][p.x - 1]];
        if(p.y != N - 1 && !used[graph[p.y + 1][p.x]]) c = graph[p.y + 1][p.x], used[graph[p.y + 1][p.x]] = true, sum += map[graph[p.y + 1][p.x]];
        if(p.x != M - 1 && !used[graph[p.y][p.x + 1]]) d = graph[p.y][p.x + 1], used[graph[p.y][p.x + 1]] = true, sum += map[graph[p.y][p.x + 1]];

        result[p.y][p.x] = (sum % 10) + '0';
        used[a] = used[b] = used[c] = used[d] = false;
    }
    result[N - 1][M] = '\0';

    printf("%s\n", result[0]);

    free(result);
    free(graph);
    delete[] used;
    delete[] map;
}