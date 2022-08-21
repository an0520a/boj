#include <stdio.h>
#include <malloc.h>

typedef unsigned int u32;
typedef unsigned long long u64;

u64 getPathNum(u32** arr, u32 N, u32 i, u32 j);

int main()
{
    u32 N;
    u32** arr;

    scanf(" %u", &N);

    arr = (u32 **)malloc(N * sizeof(u32 *));
    for (u32 i = 0; i < N; i++)
    {
        arr[i] = (u32 *)malloc(N * sizeof(u32));

        for (u32 j = 0; j < N; j++) scanf(" %u", arr[i] + j);
    }

    printf("%llu\n", getPathNum(arr, N, 0, 0));

    for (u32 i = 0; i < N; i++) free(arr[i]);
    free(arr);
}

u64 getPathNum(u32** arr, u32 N, u32 i, u32 j)
{
    static u64 memo[100][100];

    if (i == N - 1 && j == N - 1) return 1;
    else if (memo[i][j])          return memo[i][j];
    else if (arr[i][j] == 0)      return 0;
    else
    {
        return memo[i][j] = ((N > i + arr[i][j])? getPathNum(arr, N, i + arr[i][j], j) : 0) + ((N > j + arr[i][j])? getPathNum(arr, N, i, j + arr[i][j]) : 0);
    }
}