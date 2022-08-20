#include <stdio.h>
#include <queue>
#include <memory.h>

typedef unsigned int u32;

using namespace std;

void BFS_check(bool** arr, u32 size);

int main()
{
    u32 N;
    scanf(" %u", &N);

    bool** arr = new bool*[N];
    for (u32 i = 0; i < N; i++) arr[i] = new bool[N];

    for (u32 i = 0; i < N; i++)
    {
        for (u32 j = 0; j < N; j++)
        {
            u32 tmp;
            scanf(" %u", &tmp);
            arr[i][j] = tmp;
        }
    }

    BFS_check(arr, N);

    for (u32 i = 0; i < N; i++) delete[] arr[i];
    delete[] arr;
}

void BFS_check(bool** arr, u32 size)
{
    char** result = new char*[size];
    for (u32 i = 0; i < size; i++) { result[i] = new char[size * 2 + 1]; result[i][size * 2] = '\0'; memset(result[i], ' ', size * 2); }
    for (u32 i = 0; i < size; i++)
    {
        bool* visited = new bool[size]{false};

        queue<u32> que;
        que.push(i);

        while (!que.empty())
        {
            u32 vertex = que.front();

            for (u32 i = 0; i < size; i++)
            {
                if (arr[vertex][i] == true && visited[i] == false) que.push(i), visited[i] = true;
            }

            que.pop();
        }

        for (u32 j = 0; j < size; j++) if (visited[j] == true) result[i][j * 2] = '1'; else result[i][j * 2] = '0';

        delete[] visited;
    }

    for (u32 i = 0; i < size; i++)
    {
        printf("%s\n", result[i]);
    }

    for (u32 i = 0; i < size; i++) delete[] result[i];
    delete[] result;
}