#include <cstdio>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>

typedef unsigned int u32;

using namespace std;

typedef struct _point
{
    u32 y;
    u32 x;
} point;

vector<u32> BFS(char** arr, u32 size);

int main()
{
    u32 N;
    scanf(" %u", &N);

    char** arr = new char*[N + 2];

    arr[0] = new char[N + 2];
    memset(arr[0], '0', (N + 2) * sizeof(char));
    arr[N + 1] = new char[N + 2];
    memset(arr[N + 1], '0', (N + 2) * sizeof(char));

    for (u32 i = 1; i <= N; i++)
    {
        arr[i] = new char[N + 2];
        scanf(" %s", arr[i] + 1);
        arr[i][0] = '0';
        arr[i][N + 1] = '0';
    }

    /*
    printf("\n");
    for (u32 i = 0; i < N + 2; i++)
    {
        for (u32 j = 0; j < N + 2; j++)
        {
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }
    */

    vector<u32> result = BFS(arr, N);
    sort(result.begin(), result.end());

    printf("%lu\n", result.size());
    for(u32 i = 0; i < result.size(); i++)
    {
        printf("%u\n", result[i]);
    }

    for(u32 i = 0; i < N + 2; i++) delete[] arr[i];
    delete[] arr; 
}

vector<u32> BFS(char** arr, u32 size)
{
    vector<u32> result;

    for (u32 i = 1; i <= size; i++)
        for (u32 j = 1; j <= size; j++)
        {
            if (arr[i][j] == '1')
            {
                queue<point> que;
                que.push({i, j});
                arr[i][j] = '0';

                u32 count = 0;

                while (!que.empty())
                {
                    point tmp = que.front();
                    que.pop();

                    count++;

                    if (arr[tmp.y - 1][tmp.x] == '1') que.push({tmp.y - 1, tmp.x}), arr[tmp.y - 1][tmp.x] = '0';
                    if (arr[tmp.y][tmp.x + 1] == '1') que.push({tmp.y, tmp.x + 1}), arr[tmp.y][tmp.x + 1] = '0';
                    if (arr[tmp.y + 1][tmp.x] == '1') que.push({tmp.y + 1, tmp.x}), arr[tmp.y + 1][tmp.x] = '0';
                    if (arr[tmp.y][tmp.x - 1] == '1') que.push({tmp.y, tmp.x - 1}), arr[tmp.y][tmp.x - 1] = '0';
                }

                result.push_back(count);
            }
        }

    return result;
}