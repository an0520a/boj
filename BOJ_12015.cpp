#include <stdio.h>
#include <malloc.h>

typedef unsigned int u32;

u32 getSizeOfLIS(u32* arr, u32 size);
u32* lowerBound(u32* begin, u32* end, u32 val);

int main()
{
    u32 N;
    u32* arr;
    
    scanf(" %u", &N);

    arr = (u32 *)malloc(N * sizeof(u32));

    for(u32 i = 0; i < N; i++)
    {
        scanf(" %u", arr + i);
    }

    printf("%u\n", getSizeOfLIS(arr, N));

    free(arr);
}


u32 getSizeOfLIS(u32* arr, u32 size)
{
    u32* memo = (u32 *)malloc(size * sizeof(u32));
    u32 memo_size = 0;

    memo[memo_size] = arr[0], memo_size++;

    for (u32 i = 1; i < size; i++)
    {
        if(arr[i] > memo[memo_size - 1]) memo[memo_size] = arr[i], memo_size++;
        else                             (*lowerBound(memo, memo + memo_size, arr[i])) = arr[i];
    }

    free(memo);

    return memo_size;
}

u32* lowerBound(u32* begin, u32* end, u32 val)
{
    end--;

    while(end > begin)
    {
        u32* mid = begin + (end - begin) / 2;

        if(*mid >= val) end = mid;
        else            begin = mid + 1;
    }

    return end;
}