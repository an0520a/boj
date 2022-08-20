#include <stdio.h>
#include <malloc.h>
#include <memory.h>

typedef unsigned int u32;

u32 getMin(u32* arr, u32 len);
u32 getMinCMP(u32* arr, u32** memo, u32* sum, u32 start, u32 end);

int main()
{
    u32 T;
    u32 arr[500];

    scanf(" %u", &T);

    while(T--)
    {
        u32 K;
        
        scanf(" %u", &K);
        
        memset(arr, 0, K * sizeof(u32));
        for (u32 i = 0; i < K; i++) scanf(" %u", arr + i);

        printf("%u\n", getMin(arr, K));

    }
}

u32 getMin(u32* arr, u32 len)
{
    u32** memo;
    u32* sum;
    u32 result;

    memo = (u32 **)calloc(len, sizeof(u32 *));
    for (u32 i = 0; i < len; i++) memo[i] = (u32 *)calloc(len, sizeof(u32));
    sum = (u32 *)malloc(len * sizeof(u32));
    for (u32 s = 0, i = 0; i < len; i++)
    {
        s += arr[i];
        sum[i] = s;
    }

    result = getMinCMP(arr, memo, sum, 0, len - 1);

    for (u32 i = 0; i < len; i++) free(memo[i]);
    free(memo);
    free(sum);

    return result;
}

u32 getMinCMP(u32* arr, u32** memo, u32* sum, u32 start, u32 end)
{
    if (memo[start][end]) return memo[start][end];
    else if(end - start == 1) return memo[start][end] = arr[start] + arr[end];
    else if(end == start) return 0;
    else
    {
        u32 tmp = 0;
        u32 min = 0xFFFFFFFF;

        for (u32 i = start; i < end; i++)
        {
            u32 tmp = getMinCMP(arr, memo, sum, start, i) + getMinCMP(arr, memo, sum, i + 1, end);
            min = (tmp < min)? tmp : min;
        }
        if(start == 0) tmp = sum[end];
        else           tmp = sum[end] - sum[start - 1];

        return memo[start][end] = min + tmp;
    }
}