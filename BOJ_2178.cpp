#include <iostream>
#include <queue>
#include <memory.h>

typedef unsigned int u32;

typedef struct _point
{
    u32 x;
    u32 y;
} point;

using namespace std;

u32 BFS(char** arr, const point& p);

int main()
{
    u32 N, M;
    char** arr;
    scanf(" %u %u", &N, &M);
    
    arr = new char*[N + 2];
    for (u32 i = 1; i < N + 1; i++)
    {
        arr[i] = new char[M + 3];
        scanf(" %s", arr[i] + 1);
        arr[i][0] = '0';
        arr[i][M + 1] = '0';
        arr[i][M + 2] = '\0';
    }
    arr[0] = new char[M + 3];
    arr[N + 1] = new char[M + 3];
    arr[0][M + 2] = '\0';
    arr[N + 1][M + 2] = '\0';
    memset(arr[0]  , '0', (M + 2) * sizeof(char));
    memset(arr[N+1], '0', (M + 2) * sizeof(char));

    printf("%u\n", BFS(arr, {M, N}));
}

u32 BFS(char** arr, const point& p)
{
    queue<point> que;
    que.push({1, 1});
    arr[1][1] = 0;

    for (u32 i = 1;;i++)
    {
        u32 size = que.size();

        for (u32 j = 0; j < size; j++)
        {
            point tmp = que.front();
            que.pop();

            if (p.x == tmp.x && p.y == tmp.y) return i;

            if (arr[tmp.y - 1][tmp.x] == '1') que.push({tmp.x, tmp.y - 1}), arr[tmp.y - 1][tmp.x] = '0';
            if (arr[tmp.y][tmp.x + 1] == '1') que.push({tmp.x + 1, tmp.y}), arr[tmp.y][tmp.x + 1] = '0';
            if (arr[tmp.y + 1][tmp.x] == '1') que.push({tmp.x, tmp.y + 1}), arr[tmp.y + 1][tmp.x] = '0';
            if (arr[tmp.y][tmp.x - 1] == '1') que.push({tmp.x - 1, tmp.y}); arr[tmp.y][tmp.x - 1] = '0';
        }
    }
}