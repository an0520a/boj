#include <stdio.h>
#include <malloc.h>
#include <vector>
#include <queue>

typedef unsigned char u8;
typedef unsigned int u32;

typedef enum _dir
{
    hor, dig, ver
} dir;

typedef struct _point
{
    u8 y;
    u8 x;
    dir d;
} point;

using namespace std;


int main()
{
    u32 N;
    u32 result = 0;
    queue<point> que;

    scanf(" %u", &N);

    bool (*arr)[N] = (bool (*)[N])malloc(N * N * sizeof(bool));

    for (u32 i = 0; i < N; i++)
    {
        for (u32 j = 0; j < N; j++)
        {
            scanf(" %hhu", arr[i] + j);
        }
    }

    que.push({0, 1, hor});

    while (!que.empty())
    {
        point p = que.front();
        que.pop();

        if(p.y == N - 1 && p.x == N - 1) { result++; continue; }

        if ((p.d == dig || p.d == hor) && p.x != N - 1 && arr[p.y][p.x + 1] != 1) que.push({p.y, u8(p.x + 1), hor}); // 가로 이동
        if ((p.d == dig || p.d == ver) && p.y != N - 1 && arr[p.y + 1][p.x] != 1) que.push({u8(p.y + 1), p.x, ver}); // 세로 이동
        if ((p.y != N - 1 && p.x != N - 1 && arr[p.y + 1][p.x] != 1 && arr[p.y][p.x + 1] != 1 && arr[p.y + 1][p.x + 1] != 1)) que.push({u8(p.y + 1), u8(p.x + 1), dig});
    }

    printf("%u\n", result);

    free(arr);
}