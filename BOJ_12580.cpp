#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <memory.h>

typedef unsigned int u32;
typedef unsigned long long u64;

int main()
{
    u32 D;
    u32 memo[32][8][8] = 
    {
        { {0} },
        {
            {0, 1, 1, 0, 0, 0, 0, 0}, // 정보과학관 0
            {1, 0, 1, 1, 0, 0, 0, 0}, // 전산관 1
            {1, 1, 0, 1, 1, 0, 0, 0}, // 미래관 2
            {0, 1, 1, 0, 1, 1, 0, 0}, // 신앙관 3
            {0, 0, 1, 1, 0, 1, 0, 1},
            {0, 0, 0, 1, 1, 0, 1, 0},
            {0, 0, 0, 0, 0, 1, 0, 1},
            {0, 0, 0, 0, 1, 0, 1, 0}
        }
    };
    u32 (*result)[8] = (u32 (*)[8])calloc(8 * 8, sizeof(u32));
    u32 (*tmp_result)[8] = (u32 (*)[8])calloc(8 * 8, sizeof(u32));
    const u32 mod_num = 1000000007;

    for (u32 t = 2; t < 32; t++)
    {
        for (u32 i = 0; i < 8; i++)
        {
            for (u32 j = 0; j < 8; j++)
            {
                for (u32 k = 0; k < 8; k++)
                {
                    memo[t][i][k] = ((u64)memo[t][i][k] + (u64)memo[t - 1][i][j] * (u64)memo[t - 1][j][k]) % mod_num;
                }
            }
        }
    }

    scanf(" %u", &D);

    u32 i = 1;
    bool flag = true;
    do
    {
        if(D & 1)
        {
            if(flag)
            {
                for (u32 u = 0; u < 8; u++)
                {
                    for (u32 v = 0; v < 8; v++)
                    {
                        result[u][v] = memo[i][u][v];
                    }
                }

                flag = false;
            }
            else
            {
                memset(tmp_result, 0, 8 * 8 * sizeof(u32));

                for (u32 u = 0; u < 8; u++)
                {
                    for (u32 m = 0; m < 8; m++)
                    {
                        for (u32 v = 0; v < 8; v++)
                        {
                            tmp_result[u][v] = ((u64)tmp_result[u][v] + (u64)result[u][m] * (u64)memo[i][m][v]) % mod_num;
                        }
                    }
                }

                u32 (*tmp)[8] = tmp_result;
                tmp_result = result;
                result = tmp;
            }
        }

        i++;
    } while (D >>= 1);

    printf("%u\n", result[0][0]);

    free(tmp_result);
    free(result);
}