#include <stdio.h>
#include <queue>

typedef unsigned int u32;

using namespace std;

typedef struct _point
{
    u32 h;
    u32 y;
    u32 x;
} point;

int BFS(int*** arr, u32 M, u32 N, u32 H);

int main()
{
    u32 M, N, H;
    scanf(" %u %u %u", &M, &N, &H);

    int*** arr = new int**[H];

    for (u32 i = 0; i < H; i++)
    {
        arr[i] = new int*[N];

        for (u32 j = 0; j < N; j++)
        {
            arr[i][j] = new int[M];

            for (u32 k = 0; k < M; k++)
            {
                scanf(" %d", arr[i][j] + k);
            }
        }
    }

    printf("%d\n", BFS(arr, M, N, H));

    for (u32 i = 0; i < H; i++)
    {
        for (u32 j = 0; j < N; j++) { delete[] arr[i][j]; }

        delete[] arr[i];
    }
    delete[] arr;
}

int BFS(int*** arr, u32 M, u32 N, u32 H)
{
    queue<point> que;
    int day = -1;

    for (u32 i = 0; i < H; i++)
    {
        for (u32 j = 0; j < N; j++)
        {
            for (u32 k = 0; k < M; k++)
            {
                if (arr[i][j][k] == 1) que.push(point{i, j, k});
            }
        }
    }

    while(!que.empty())
    {
        u32 size = que.size();
        
        for (u32 i = 0; i < size; i++)
        {
            point p = que.front();
            que.pop();

            if (p.h != 0     && arr[p.h - 1][p.y][p.x] == 0) que.push({p.h - 1, p.y, p.x}), arr[p.h - 1][p.y][p.x] = 1;
            if (p.h != H - 1 && arr[p.h + 1][p.y][p.x] == 0) que.push({p.h + 1, p.y, p.x}), arr[p.h + 1][p.y][p.x] = 1;
            if (p.y != 0     && arr[p.h][p.y - 1][p.x] == 0) que.push({p.h, p.y - 1, p.x}), arr[p.h][p.y - 1][p.x] = 1;
            if (p.y != N - 1 && arr[p.h][p.y + 1][p.x] == 0) que.push({p.h, p.y + 1, p.x}), arr[p.h][p.y + 1][p.x] = 1;
            if (p.x != 0     && arr[p.h][p.y][p.x - 1] == 0) que.push({p.h, p.y, p.x - 1}), arr[p.h][p.y][p.x - 1] = 1;
            if (p.x != M - 1 && arr[p.h][p.y][p.x + 1] == 0) que.push({p.h, p.y, p.x + 1}), arr[p.h][p.y][p.x + 1] = 1;
        }

        day++;
    }

    for (u32 i = 0; i < H; i++)
    {
        for (u32 j = 0; j < N; j++)
        {
            for (u32 k = 0; k < M; k++)
            {
                if(arr[i][j][k] == 0) return -1;
            }
        }
    }

    return day;
}