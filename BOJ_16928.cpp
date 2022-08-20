#include <stdio.h>
#include <queue>

typedef unsigned int u32;

using namespace std;

u32 BFS(u32* arr);

int main()
{
    u32 N, M;
    u32 arr[101] = { 0 };

    scanf(" %u %u", &N, &M);

    for (u32 i = 0; i < N; i++)
    {
        u32 u, v;
        scanf(" %u %u", &u, &v);
        arr[u] = v;
    }
    for (u32 j = 0; j < M; j++)
    {
        u32 u, v;
        scanf(" %u %u", &u, &v);
        arr[u] = v;
    }

    printf("%u\n", BFS(arr));
}

u32 BFS(u32* arr)
{
    bool visited[101] = { false };
    queue<u32> que;
    que.push(1);
    u32 mov = 0;

    while(!que.empty())
    {
        mov++;

        const u32 size = que.size();

        for (u32 i = 0; i < size; i++)
        {
            u32 pos = que.front();
            que.pop();
            const u32 flag = (100 - pos < 6)? 100 - pos : 6;

            for (u32 j = 1; j <= flag; j++)
            {
                u32 next_pos = (arr[pos + j] == 0)? pos + j : arr[pos + j];

                if (next_pos == 100) return mov;
                else if (visited[next_pos] == false)
                {
                    que.push(next_pos);
                    visited[next_pos] = true;
                }
            }
        }
    }
}