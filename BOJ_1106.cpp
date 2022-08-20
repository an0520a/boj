#include <cstdio>
#include <malloc.h>
#include <memory.h>

typedef unsigned int u32;

typedef struct _entry
{
    u32 w;
    u32 v;
} entry;

using namespace std;

int main()
{
    u32 C, N;
    entry* arr;
    u32 memo[1001];

    scanf(" %u %u", &C, &N);

    arr = (entry *)malloc(N * sizeof(entry));

    for (u32 i = 0; i < N; i++)
    {
        u32 w, v;
        scanf(" %u %u", &w, &v);

        arr[i].w = w, arr[i].v = v;
    }

    memo[0] = 0;
    memset(memo + 1, 0xFF, 1000 * sizeof(u32));
    for (u32 i = 1; i <= C; i++)
    {
        for (u32 j = 0; j < N; j++)
        {
            if(arr[j].v > i)
            {
                memo[i] = (arr[j].w < memo[i])? arr[j].w : memo[i];
            }
            else
            {
                memo[i] = (memo[i - arr[j].v] + arr[j].w < memo[i])? memo[i - arr[j].v] + arr[j].w : memo[i];
            }
        }
    }

    printf("%u\n", memo[C]);

    free(arr);
}