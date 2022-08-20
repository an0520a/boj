#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <memory.h>

typedef unsigned int u32;
typedef struct _stuff
{
    u32 weight;
    u32 value;
} stuff;

using namespace std;

u32 getMaxValue(u32 bagSize, stuff* stuck, u32 stuckSize);

int main()
{
    u32 N, K;
    scanf(" %u %u", &N, &K);

    stuff* stuck = (stuff *)malloc((N) * sizeof(stuff));

    for (u32 i = 0; i < N; i++)
    {
        scanf(" %u %u", &stuck[i].weight, &stuck[i].value);
    }

    printf("%u\n", getMaxValue(K, stuck, N));
}

u32 getMaxValue(u32 bagSize, stuff* stuck, u32 stuckSize)
{
    u32 max;
    u32 (*wv)[bagSize + 1] = (u32 (*)[bagSize + 1])malloc(stuckSize * (bagSize + 1) * sizeof(u32));

    for (u32 j = 0; j <= bagSize; j++)
    {
        wv[0][j] = (stuck[0].weight <= j)? stuck[0].value : 0;
    }

    for (u32 i = 1; i < stuckSize; i++)
    {
        for (u32 j = 0; j <= bagSize; j++)
        {
            wv[i][j] = (j >= stuck[i].weight && wv[i - 1][j - stuck[i].weight] + stuck[i].value > wv[i - 1][j])? wv[i - 1][j - stuck[i].weight] + stuck[i].value : wv[i - 1][j];
        }
    }

    max = wv[stuckSize - 1][bagSize];

    free(wv);

    return max;
}