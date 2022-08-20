#include <stdio.h>
#include <queue>
#include <map>

typedef unsigned int u32;

using namespace std;

void BFS(u32 A, u32 B);

int main()
{
    u32 A, B;
    scanf(" %u %u", &A, &B);

    BFS(A, B);
}

void BFS(u32 A, u32 B)
{
    u32 time = 0;

    queue<u32> que;
    que.push(A);

    while(!que.empty())
    {
        time++;

        u32 size = que.size();

        for (u32 i = 0; i < size; i++)
        {
            u32 pos = que.front();
            que.pop();

            if(pos == B) { printf("%u\n", time); return; }

            if (pos <   100000000U) que.push(pos * 10 + 1);
            if (pos <=  500000000U) que.push(pos * 2);
        }
    }

    printf("-1\n");
}