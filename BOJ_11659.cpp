#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned int u32;

u32 getSum(u32* arr, u32 i, u32 j);

int main()
{
    u32 N, M;
    u32* arr;
    scanf(" %u %u", &N, &M);

    arr = (u32 *)malloc((N + 1) * sizeof(u32));

    for (u32 i = 1; i < N + 1; i++) scanf(" %u", arr + i);
    
    for (u32 i = 0; i < M; i++)
    {
        u32 a, b;
        scanf(" %u %u", &a, &b);

        printf("%u\n", getSum(arr, a, b));
    }

    free(arr);
}

u32 getSum(u32* arr, u32 i, u32 j)
{
    static u32 sum[100001] = { 0 };
    static u32 max = 0;

    if (j <= max) return sum[j] - sum[i - 1];
    else
    {
        for(;max < j; max++)
        {
            sum[max + 1] = sum[max] + arr[max + 1];
        }

        return sum[j] - sum[i - 1];
    }
}