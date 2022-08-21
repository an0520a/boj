#include <stdio.h>
#include <queue>

typedef unsigned short u16;
typedef unsigned int u32;

using namespace std;

void find(u32 x, u32 y);

int main()
{
    u32 N, M;
    scanf(" %u %u", &N, &M);

    find(N, M);
}

void find(u32 x, u32 y)
{
    bool visited[100001] = { false };
    u32 time = 0;
    u32 count = 0;
    bool flag = true;
    queue<u32> que;

    que.push({x});

    while (flag)
    {
        u32 size = que.size();

        for (u32 i = 0; i < size; i++)
        {
            u32 p = que.front();
            que.pop();
            visited[p] = true;

            if (p == y)
                flag = false, count++;

            if (p <=  50000 && !visited[p * 2]) que.push(p * 2);
            if (p !=      0 && !visited[p - 1]) que.push(p - 1);
            if (p != 100000 && !visited[p + 1]) que.push(p + 1);
        }

        time++;
    }
    time--;

    printf("%u \n%u \n", time, count);
}