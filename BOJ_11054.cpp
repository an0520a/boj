#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

typedef unsigned int u32;

u32 maxLen(u32* arr, u32 len);

int main()
{
    u32 N;
    u32* arr;

    scanf(" %u", &N);

    arr = (u32 *)malloc(N * sizeof(u32));

    for (u32 i = 0; i < N; i++)
    {
        scanf(" %u", arr + i);
    }

    printf("%u\n", maxLen(arr, N));

    free(arr);
}

u32 maxLen(u32* arr, u32 len)
{
    u32* lenR = (u32 *)malloc(len * sizeof(u32));
    u32* lenL = (u32 *)malloc(len * sizeof(u32));
    u32 result = 1;

    for (u32 i = 0; i < len; i++)
    {
        u32 max = 0;
        
        for(u32 j = 0; j < i; j++)
        {
            if(arr[j] < arr[i])
            {
                max = (lenL[j] + 1 > max)? lenL[j] + 1 : max;
            }
        }

        lenL[i] = max;
    }

    for (u32 i = len - 1; !(i & 0x80000000); i--)
    {
        u32 max = 0;
        
        for(u32 j = len - 1; j > i; j--)
        {
            if(arr[j] < arr[i])
            {
                max = (lenR[j] + 1 > max)? lenR[j] + 1 : max;
            }
        }

        lenR[i] = max;
    }

    for (u32 i = 0; i < len; i++) result = (lenL[i] + lenR[i] + 1 > result)? lenL[i] + lenR[i] + 1 : result;

    free(lenR);
    free(lenL);

    return result;
}