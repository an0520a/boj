#include <stdio.h>
#include <malloc.h>

typedef unsigned int u32;

u32 getMaxLen(u32* arr, u32 size);
u32 getMaxLen_compute(u32* memo, u32* arr, u32 index, u32 size);

int main()
{
    u32 N;
    u32 *arr;

    scanf(" %u", &N);

    arr = (u32 *)malloc(N * sizeof(u32));

    for(u32 i = 0; i < N; i++)
    {
        scanf(" %u", arr + i);
    }

    printf("%u\n", getMaxLen(arr, N));

    free(arr);
}

u32 getMaxLen(u32* arr, u32 size)
{
    u32* memo = (u32 *)calloc(size, sizeof(u32));
    u32 result = 0;

    for (u32 i = 0; i < size; i++) result = (getMaxLen_compute(memo, arr, i, size) > result)? getMaxLen_compute(memo, arr, i, size) : result;

    free(memo);

    return result;
}

u32 getMaxLen_compute(u32* memo, u32* arr, u32 index, u32 size)
{
    if (memo[index]) return memo[index];
    else
    {
        u32 max = 0;

        for (u32 i = index + 1; i < size; i++)
        {
            if(arr[index] < arr[i])
            {
                max = (getMaxLen_compute(memo, arr, i, size) > max)? getMaxLen_compute(memo, arr, i, size) : max;
            }
        }

        return memo[index] = max + 1;
    }
}