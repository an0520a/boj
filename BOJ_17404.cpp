#include <cstdio>
#include <malloc.h>
#include <memory.h>

typedef unsigned int u32;

int main()
{
    u32 N;
    u32 result = 0xFFFFFFFF;
    u32 (*arr)[3];
    u32 (*memo)[3];
    auto min = [](const u32& x, const u32& y)->const u32&{ return (x < y)? x : y; };

    scanf(" %u", &N);

    arr = (u32 (*)[3])malloc(N * 3 * sizeof(u32));
    memo = (u32 (*)[3])malloc(N * 3 * sizeof(u32));

    for (u32 i = 0; i < N; i++)
    {
        scanf(" %u %u %u", arr[i] + 0, arr[i] + 1, arr[i] + 2);
    }

    for (u32 t = 0; t < 3; t++)
    {
        memset(memo[0], 0x7F, 3 * sizeof(u32));
        memo[0][t] = arr[0][t];

        for (u32 i = 1; i < N; i++)
        {
            memo[i][0] = arr[i][0] + min(memo[i - 1][1], memo[i - 1][2]);
            memo[i][1] = arr[i][1] + min(memo[i - 1][0], memo[i - 1][2]);
            memo[i][2] = arr[i][2] + min(memo[i - 1][0], memo[i - 1][1]);
        }

        if(t != 0) result = (result < memo[N - 1][0])? result : memo[N - 1][0];
        if(t != 1) result = (result < memo[N - 1][1])? result : memo[N - 1][1];
        if(t != 2) result = (result < memo[N - 1][2])? result : memo[N - 1][2];
    }

    free(memo);
    free(arr);

    printf("%u\n", result);
}