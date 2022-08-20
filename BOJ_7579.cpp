#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <algorithm>

typedef unsigned int u32;

typedef struct _entry
{
    u32 memory;
    u32 cost;
} entry;

using namespace std;

int main()
{
    u32 N, M;
    entry* ram;

    scanf(" %u %u", &N, &M);

    ram = (entry *)malloc((N + 1) * sizeof(entry));

    for (u32 i = 1; i <= N; i++) scanf(" %u", &ram[i].memory);
    for (u32 i = 1; i <= N; i++) scanf(" %u", &ram[i].cost);

    u32 *memo = (u32 *)malloc((M + 1) * sizeof(u32));
    u32 *tmp = (u32 *)malloc((M + 1) * sizeof(u32));
    memset(memo, 0x7F, (M + 1) * sizeof(u32));
    memo[0] = 0;
    tmp[0] = 0;
    
    for (u32 i = 1; i <= N; i++)
    {
        for (u32 m = 1; m <= M; m++)
        {
            if(ram[i].memory >= m)
            {
                tmp[m] = (ram[i].cost < memo[m])? ram[i].cost : memo[m];
            }
            else
            {
                tmp[m] = (memo[m - ram[i].memory] + ram[i].cost < memo[m])? memo[m - ram[i].memory] + ram[i].cost : memo[m];
            }
        }

        u32 *swap_tmp = tmp;
        tmp = memo;
        memo = swap_tmp;
    }

    printf("%u\n", memo[M]);

    free(ram);
    free(memo);
    free(tmp);
}