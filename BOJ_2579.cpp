#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned int u32;

u32 getScore(u32* arr, u32 pos);

int main()
{
    u32 N;
    u32* arr;

    scanf(" %u", &N);

    arr = (u32 *)malloc((N + 1) * sizeof(u32));

    for (u32 i = 1; i <= N; i++)
    {
        scanf(" %u", arr + i);
    }

    u32 result = getScore(arr, N);
    printf("%u\n", result);
}

u32 getScore(u32* arr, u32 pos)
{
    static u32 score[301] = { 0 };

    if      (score[pos]) return score[pos];
    else if (pos == 0)   return 0;
    else if (pos == 1) { score[1] = arr[1];          return score[1]; }
    else if (pos == 2) { score[2] = arr[1] + arr[2]; return score[2]; }

    score[pos] = (getScore(arr, pos - 3) + arr[pos - 1] + arr[pos] > getScore(arr, pos - 2) + arr[pos])? 
    getScore(arr, pos - 3) + arr[pos - 1] + arr[pos] : getScore(arr, pos - 2) + arr[pos];

    return score[pos];
}