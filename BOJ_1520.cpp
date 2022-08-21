#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef long long i64;

u32 getMin(u16** map, u16 M, u16 N);
u32 getMin_cmp(u16** map, u32** memo, bool** calculated, u16 y, u16 x, u16 M, u16 N);

int main()
{
    u16 M, N;
    u16** map;

    scanf(" %hu %hu", &M, &N);

    map = (u16 **)malloc(M * sizeof(u16 *));
    for (u16 i = 0; i < M; i++)
    {
        map[i] = (u16 *)malloc(N * sizeof(u16));

        for (u16 j = 0; j < N; j++)
        {
            scanf(" %hu", &map[i][j]);
        }
    }

    printf("%u\n", getMin(map, M, N));

    for (u16 i = 0; i < M; i++) free(map[i]);
    free(map);
}

u32 getMin(u16** map, u16 M, u16 N)
{
    u32 result = 0;
    u32** memo = (u32 **)calloc(M, sizeof(u32 *));
    bool** calculated = (bool **)calloc(M, sizeof(bool *));
    for (u16 i = 0; i < M; i++) memo[i] = (u32 *)calloc(N, sizeof(u32));
    for (u16 i = 0; i < M; i++) calculated[i] = (bool *)calloc(N, sizeof(bool));
    calculated[M - 1][N - 1] = true;
    memo[M - 1][N - 1] = 1;

    result = getMin_cmp(map, memo, calculated, 0, 0, M, N);

    for (u16 i = 0; i < M; i++) free(memo[i]), free(calculated[i]);
    free(calculated);
    free(memo);

    return result;
}

u32 getMin_cmp(u16** map, u32** memo, bool** calculated, u16 y, u16 x, u16 M, u16 N)
{
    if(calculated[y][x]) return memo[y][x];
    else
    {
        calculated[y][x] = true;
        u32 count = 0;

        if(y != 0 && map[y - 1][x] < map[y][x])
        {
            if(calculated[y - 1][x]) count += memo[y - 1][x];
            else count += getMin_cmp(map, memo, calculated, y - 1, x, M, N);
        }
        if(x != 0 && map[y][x - 1] < map[y][x])
        {
            if(calculated[y][x - 1]) count += memo[y][x - 1];
            else count += getMin_cmp(map, memo, calculated, y, x - 1, M, N);
        }
        if(y != M - 1 && map[y + 1][x] < map[y][x])
        {
            if(calculated[y + 1][x]) count += memo[y + 1][x];
            else count += getMin_cmp(map, memo, calculated, y + 1, x, M, N);
        }
        if(x != N - 1 && map[y][x + 1] < map[y][x])
        {
            if(calculated[y][x + 1]) count += memo[y][x + 1];
            else count += getMin_cmp(map, memo, calculated, y, x + 1, M, N);
        }

        return memo[y][x] = count;
    }
}