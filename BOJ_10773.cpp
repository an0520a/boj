#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <queue>
#include <vector>

typedef unsigned int u32;
typedef unsigned long long u64;

int main()
{
    u32 N, M;
    u32 arr[10001] = {0};
    scanf(" %u", &N);

    std::priority_queue<u32, std::vector<u32>, std::greater<u32>> que;

    M = N;

    while(M--)
    {
        u32 K;
        scanf(" %u", &K);

        if(arr[K] == 0) que.push(K);

        arr[K]++;
    }

    while(!que.empty())
    {
        u32 tmp = que.top();
        que.pop();

        while(arr[tmp]--)
        {
            printf("%u\n", tmp);
        }
    }
}