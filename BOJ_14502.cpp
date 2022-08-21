#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <queue>

typedef unsigned char u8;
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
    u32 maxClearZoneSize = 0;
    point pointArr[64];
    queue<point> virus;
    u32 pointArrSize = 0;
    scanf(" %u %u", &N, &M);

    u8 (*graph)[M] = (u8 (*)[M])malloc(N * M * sizeof(u8));
    u8 (*tmpGraph)[M] = (u8 (*)[M])malloc(N * M * sizeof(u8));

    for (u32 i = 0; i < N; i++)
    {
        for (u32 j = 0; j < M; j++)
        {
            u32 tmp;
            scanf(" %u", &tmp);

            graph[i][j] = tmp;

            if      (tmp == 0) pointArr[pointArrSize] = {i, j}, pointArrSize++;
            else if (tmp == 2) virus.push({i, j});
        }
    }

    for (u32 i = 0; i < pointArrSize; i++)
    {
        for (u32 j = i + 1; j < pointArrSize; j++)
        {
            for (u32 k = j + 1; k < pointArrSize; k++)
            {
                memcpy(tmpGraph, graph, N * M * sizeof(u8));

                tmpGraph[pointArr[i].y][pointArr[i].x] = 1;
                tmpGraph[pointArr[j].y][pointArr[j].x] = 1;
                tmpGraph[pointArr[k].y][pointArr[k].x] = 1;

                queue<point> que = virus;
                u32 clearZoneSize = pointArrSize - 3;

                while (!que.empty())
                {
                    point p = que.front();
                    que.pop();

                    if(p.y != 0     && tmpGraph[p.y - 1][p.x] == 0) que.push({p.y - 1, p.x}), tmpGraph[p.y - 1][p.x] = 2, clearZoneSize--;
                    if(p.y != N - 1 && tmpGraph[p.y + 1][p.x] == 0) que.push({p.y + 1, p.x}), tmpGraph[p.y + 1][p.x] = 2, clearZoneSize--;
                    if(p.x != 0     && tmpGraph[p.y][p.x - 1] == 0) que.push({p.y, p.x - 1}), tmpGraph[p.y][p.x - 1] = 2, clearZoneSize--;
                    if(p.x != M - 1 && tmpGraph[p.y][p.x + 1] == 0) que.push({p.y, p.x + 1}), tmpGraph[p.y][p.x + 1] = 2, clearZoneSize--;
                }

                maxClearZoneSize = (clearZoneSize > maxClearZoneSize)? clearZoneSize : maxClearZoneSize;
            }
        }
    }

    printf("%u\n", maxClearZoneSize);

    free(graph);
    free(tmpGraph);
}