#include <stdio.h>
#include <memory.h>
#include <queue>

typedef unsigned int u32;

typedef struct _entry
{
    u32 y;
    u32 x;
    bool energy;
} entry;

using namespace std;

int BFS(char** arr, const u32& N, const u32& M);

int main()
{
    u32 N, M;
    char** arr;
    scanf(" %u %u", &N, &M);

    arr = new char*[N + 2];
    arr[0] = new char[M + 3];
    arr[N + 1] = new char[M + 3];
    memset(arr[0], '9', (M + 2) * sizeof(char));
    memset(arr[N + 1], '9', (M + 2) * sizeof(char));
    arr[0][M + 2] = '\0';   
    arr[N + 1][M + 2] = '\0';

    for (u32 i = 1; i < N + 1; i++)
    {
        arr[i] = new char[M + 3];
        scanf(" %s", arr[i] + 1);
        arr[i][0] = '9';
        arr[i][M + 1] = '9';
        arr[i][M + 2] = '\0';
    }

    printf("%d\n", BFS(arr, N, M));

    for (u32 i = 0; i < N + 2; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}

int BFS(char** arr, const u32& N, const u32& M)
{
    queue<entry> que;
    que.push({1, 1, true});
    arr[1][1] = '9';
    int dist = 1;

    while(!que.empty())
    {
        u32 size = que.size();

        for (u32 i = 0; i < size; i++)
        {
            entry tmp = que.front();
            que.pop();

            if(tmp.y == N && tmp.x == M) return dist;

            if ((arr[tmp.y - 1][tmp.x] == '0' || arr[tmp.y - 1][tmp.x] == '8') && tmp.energy) que.push({tmp.y - 1, tmp.x, true}), arr[tmp.y - 1][tmp.x] = '9';
            if ((arr[tmp.y + 1][tmp.x] == '0' || arr[tmp.y + 1][tmp.x] == '8') && tmp.energy) que.push({tmp.y + 1, tmp.x, true}), arr[tmp.y + 1][tmp.x] = '9';
            if ((arr[tmp.y][tmp.x - 1] == '0' || arr[tmp.y][tmp.x - 1] == '8') && tmp.energy) que.push({tmp.y, tmp.x - 1, true}), arr[tmp.y][tmp.x - 1] = '9';
            if ((arr[tmp.y][tmp.x + 1] == '0' || arr[tmp.y][tmp.x + 1] == '8') && tmp.energy) que.push({tmp.y, tmp.x + 1, true}), arr[tmp.y][tmp.x + 1] = '9';
            if (arr[tmp.y - 1][tmp.x] == '0' && !tmp.energy) que.push({tmp.y - 1, tmp.x, false}), arr[tmp.y - 1][tmp.x] = '8';
            if (arr[tmp.y + 1][tmp.x] == '0' && !tmp.energy) que.push({tmp.y + 1, tmp.x, false}), arr[tmp.y + 1][tmp.x] = '8';
            if (arr[tmp.y][tmp.x - 1] == '0' && !tmp.energy) que.push({tmp.y, tmp.x - 1, false}), arr[tmp.y][tmp.x - 1] = '8';
            if (arr[tmp.y][tmp.x + 1] == '0' && !tmp.energy) que.push({tmp.y, tmp.x + 1, false}), arr[tmp.y][tmp.x + 1] = '8';
            if (arr[tmp.y - 1][tmp.x] == '1' && tmp.energy) que.push({tmp.y - 1, tmp.x, false});
            if (arr[tmp.y + 1][tmp.x] == '1' && tmp.energy) que.push({tmp.y + 1, tmp.x, false});
            if (arr[tmp.y][tmp.x - 1] == '1' && tmp.energy) que.push({tmp.y, tmp.x - 1, false});
            if (arr[tmp.y][tmp.x + 1] == '1' && tmp.energy) que.push({tmp.y, tmp.x + 1, false});
        }

        dist++;
    }

    return -1;
}