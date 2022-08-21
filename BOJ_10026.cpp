#include <cstdio>
#include <memory.h>
#include <queue>

typedef unsigned int u32;

using namespace std;

typedef struct _point
{
    u32 y;
    u32 x;
} point;

u32 BFS_RG_weakness(char** arr, u32 size);
u32 BFS_normal(char** arr, u32 size);

int main()
{
    u32 N;
    char** arr;
    scanf(" %u", &N);

    arr = new char*[N];
    for (u32 i = 0; i < N; i++)
    {
        arr[i] = new char[N + 1];
        scanf(" %s", arr[i]);
    }

    u32 RG_w = BFS_RG_weakness(arr, N);
    u32 normal = BFS_normal(arr, N);

    printf("%u %u\n", normal, RG_w);

    for (u32 i = 0; i < N; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}

u32 BFS_RG_weakness(char** arr, u32 size)
{
    bool** visited = new bool*[size];
    for (u32 i = 0; i < size; i++) visited[i] = new bool[size]{ 0 };
    u32 count = 0;

    for (u32 i = 0; i < size; i++)
    {
        for (u32 j = 0; j < size; j++)
        {
            if (visited[i][j] == 0)
            {
                if (arr[i][j] != 'B')
                {
                    queue<point> que;
                    que.push({i, j});

                    while (!que.empty())
                    {
                        point p = que.front();
                        que.pop();

                        if (p.y != 0 && visited[p.y - 1][p.x] == false && arr[p.y - 1][p.x] != 'B') que.push({p.y - 1, p.x}), visited[p.y - 1][p.x] = true;
                        if (p.x != 0 && visited[p.y][p.x - 1] == false && arr[p.y][p.x - 1] != 'B') que.push({p.y, p.x - 1}), visited[p.y][p.x - 1] = true;
                        if (p.y != size - 1 && visited[p.y + 1][p.x] == false && arr[p.y + 1][p.x] != 'B') que.push({p.y + 1, p.x}), visited[p.y + 1][p.x] = true;
                        if (p.x != size - 1 && visited[p.y][p.x + 1] == false && arr[p.y][p.x + 1] != 'B') que.push({p.y, p.x + 1}), visited[p.y][p.x + 1] = true;
                    }
                }
                else
                {
                    queue<point> que;
                    que.push({i, j});

                    while (!que.empty())
                    {
                        point p = que.front();
                        que.pop();

                        if (p.y != 0 && visited[p.y - 1][p.x] == false && arr[p.y - 1][p.x] == 'B') que.push({p.y - 1, p.x}), visited[p.y - 1][p.x] = true;
                        if (p.x != 0 && visited[p.y][p.x - 1] == false && arr[p.y][p.x - 1] == 'B') que.push({p.y, p.x - 1}), visited[p.y][p.x - 1] = true;
                        if (p.y != size - 1 && visited[p.y + 1][p.x] == false && arr[p.y + 1][p.x] == 'B') que.push({p.y + 1, p.x}), visited[p.y + 1][p.x] = true;
                        if (p.x != size - 1 && visited[p.y][p.x + 1] == false && arr[p.y][p.x + 1] == 'B') que.push({p.y, p.x + 1}), visited[p.y][p.x + 1] = true;
                    }
                }

                count++;
            }
        }
    }

    for (u32 i = 0; i < size; i++) delete[] visited[i];
    delete[] visited;

    return count;
}

u32 BFS_normal(char** arr, u32 size)
{
    bool** visited = new bool*[size];
    for (u32 i = 0; i < size; i++) visited[i] = new bool[size]{ 0 };
    u32 count = 0;

    for (u32 i = 0; i < size; i++)
    {
        for (u32 j = 0; j < size; j++)
        {
            if (visited[i][j] == 0)
            {
                queue<point> que;
                que.push({i, j});
                char color = arr[i][j];

                while (!que.empty())
                {
                    point p = que.front();
                    que.pop();

                    if (p.y != 0 && visited[p.y - 1][p.x] == false && arr[p.y - 1][p.x] == color) que.push({p.y - 1, p.x}), visited[p.y - 1][p.x] = true;
                    if (p.x != 0 && visited[p.y][p.x - 1] == false && arr[p.y][p.x - 1] == color) que.push({p.y, p.x - 1}), visited[p.y][p.x - 1] = true;
                    if (p.y != size - 1 && visited[p.y + 1][p.x] == false && arr[p.y + 1][p.x] == color) que.push({p.y + 1, p.x}), visited[p.y + 1][p.x] = true;
                    if (p.x != size - 1 && visited[p.y][p.x + 1] == false && arr[p.y][p.x + 1] == color) que.push({p.y, p.x + 1}), visited[p.y][p.x + 1] = true;
                }

                count++;
            }
        }
    }

    for (u32 i = 0; i < size; i++) delete[] visited[i];
    delete[] visited;

    return count;
}