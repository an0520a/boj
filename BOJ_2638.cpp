#include <stdio.h>
#include <queue>

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct _point
{
    u8 y;
    u8 x;
} point;

using namespace std;

u32 cheese_BFS(bool** arr, u32 N, u32 M);

int main()
{
    u32 N, M;
    scanf(" %u %u", &N, &M);

    bool** arr = new bool*[N];
    for (u32 i = 0; i < N; i++)
    {
        arr[i] = new bool[M];

        for (u32 j = 0; j < M; j++)
        {
            u32 tmp;
            scanf(" %u", &tmp);
            arr[i][j] = tmp;
        }
    }

    printf("%u\n", cheese_BFS(arr, N, M));

    for (u32 i = 0; i < N; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}

u32 cheese_BFS(bool** arr, u32 N, u32 M)
{
    u32 time = 0;
    queue<point> air;
    queue<point> que;
    bool** visited = new bool*[N];
    for (u32 i = 0; i < N; i++) visited[i] = new bool[M]{ false };

    air.push({0, 0});

    while (!que.empty() || !air.empty())
    {
        time++;

        while (!air.empty())
        {
            point p = air.front();
            air.pop();

            if      (p.y != 0     && arr[p.y - 1][p.x] == 1) { que.push({p.y, p.x}); }
            else if (p.x != 0     && arr[p.y][p.x - 1] == 1) { que.push({p.y, p.x}); }
            else if (p.y != N - 1 && arr[p.y + 1][p.x] == 1) { que.push({p.y, p.x}); }
            else if (p.x != M - 1 && arr[p.y][p.x + 1] == 1) { que.push({p.y, p.x}); }

            if (p.y != 0     && visited[p.y - 1][p.x] == false && arr[p.y - 1][p.x] == 0) { visited[p.y - 1][p.x] = true; air.push({(u8)(p.y - 1), p.x}); }
            if (p.x != 0     && visited[p.y][p.x - 1] == false && arr[p.y][p.x - 1] == 0) { visited[p.y][p.x - 1] = true; air.push({p.y, (u8)(p.x - 1)}); }
            if (p.y != N - 1 && visited[p.y + 1][p.x] == false && arr[p.y + 1][p.x] == 0) { visited[p.y + 1][p.x] = true; air.push({(u8)(p.y + 1), p.x}); }
            if (p.x != M - 1 && visited[p.y][p.x + 1] == false && arr[p.y][p.x + 1] == 0) { visited[p.y][p.x + 1] = true; air.push({p.y, (u8)(p.x + 1)}); }
        }

        u32 size = que.size();
        bool flag = true;

        for (u32 i = 0; i < size; i++)
        {
            point p = que.front();
            que.pop();

            if (p.y != 0 && arr[p.y - 1][p.x] == 1)
            {
                if (visited[p.y - 1][p.x] == false)
                {
                    visited[p.y - 1][p.x] = true;
                }
                else
                {
                    arr[p.y - 1][p.x] = 0;
                    air.push({(u8)(p.y - 1), p.x});
                    flag = false;
                }
            }
            if (p.x != 0 && arr[p.y][p.x - 1] == 1)
            {
                if (visited[p.y][p.x - 1] == false)
                {
                    visited[p.y][p.x - 1] = true;
                }
                else
                {
                    arr[p.y][p.x - 1] = 0;
                    air.push({p.y, (u8)(p.x - 1)});
                    flag = false;
                }
            }
            if (p.y != N - 1 && arr[p.y + 1][p.x] == 1)
            {
                if (visited[p.y + 1][p.x] == false)
                {
                    visited[p.y + 1][p.x] = true;
                }
                else
                {
                    arr[p.y + 1][p.x] = 0;
                    air.push({(u8)(p.y + 1), p.x});
                    flag = false;
                }
            }
            if (p.x != M - 1 && arr[p.y][p.x + 1] == 1)
            {
                if (visited[p.y][p.x + 1] == false)
                {
                    visited[p.y][p.x + 1] = true;
                }
                else
                {
                    arr[p.y][p.x + 1] = 0;
                    air.push({p.y, (u8)(p.x + 1)});
                    flag = false;
                }
            }
        }

        if (flag) time--;
    }

    for (u32 i = 0; i < M; i++) delete[] visited[i];
    delete[] visited;

    return time;
}