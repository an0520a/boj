#include <stdio.h>
#include <malloc.h>

typedef unsigned int u32;

u32 getMax(u32** map, u32 N);
u32 getMax_cmp(u32 **map, u32 **memo, u32 N, u32 y, u32 x);

int main()
{
    u32 N;
    u32 **map;

    scanf(" %u", &N);

    map = (u32 **)malloc(N * sizeof(u32 *));
    for (u32 i = 0; i < N; i++)
    {
        map[i] = (u32 *)malloc(N * sizeof(u32));
        for(u32 j = 0; j < N; j++) scanf(" %u", &map[i][j]);
    }

    printf("%u\n", getMax(map, N));

    for (u32 i = 0; i < N; i++) free(map[i]);
    free(map);
}

u32 getMax(u32** map, u32 N)
{
    u32 max = 0;
    u32** memo = (u32 **)calloc(N, sizeof(u32 *));
    for (u32 i = 0; i < N; i++) memo[i] = (u32 *)calloc(N, sizeof(u32));

    for (u32 i = 0; i < N; i++)
        for(u32 j = 0; j < N; j++)
            max = (getMax_cmp(map, memo, N, i, j) > max)? getMax_cmp(map, memo, N, i, j) : max;

    for (u32 i = 0; i < N; i++) free(memo[i]);
    free(memo);

    return max;
}

u32 getMax_cmp(u32 **map, u32 **memo, u32 N, u32 y, u32 x)
{
    if(memo[y][x]) return memo[y][x];
    else
    {
        u32 max = 0;

        if(y != 0 && map[y - 1][x] > map[y][x]) max = (getMax_cmp(map, memo, N, y - 1, x) > max)? getMax_cmp(map, memo, N, y - 1, x) : max;
        if(x != 0 && map[y][x - 1] > map[y][x]) max = (getMax_cmp(map, memo, N, y, x - 1) > max)? getMax_cmp(map, memo, N, y, x - 1) : max;
        if(y != N - 1 && map[y + 1][x] > map[y][x]) max = (getMax_cmp(map, memo, N, y + 1, x) > max)? getMax_cmp(map, memo, N, y + 1, x) : max;
        if(x != N - 1 && map[y][x + 1] > map[y][x]) max = (getMax_cmp(map, memo, N, y, x + 1) > max)? getMax_cmp(map, memo, N, y, x + 1) : max;

        return memo[y][x] = max + 1;
    }
}