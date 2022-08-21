#include <stdio.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef __uint128_t u128;

using namespace std;

int main()
{
    u32 N;
    u32 result = 0;
    scanf(" %u", &N);

    u32 memo[101][10][0b10000000000] = { 0 };

    for (u32 i = 1; i < 10; i++) memo[1][i][0b1 << i] = 1;

    for (u32 i = 2; i <= N; i++)
    {
        for (u32 k = 0; k < 0b10000000000; k++) if(memo[i - 1][0][k]) memo[i][1][k | 0b0000000010] = (memo[i][1][k | 0b0000000010] + memo[i - 1][0][k]) % 1000000000U;

        for (u32 j = 1; j < 9; j++)
        {
            for (u32 k = 0; k < 0b10000000000; k++)
                if(memo[i - 1][j][k])
                {
                    memo[i][j - 1][k | (0b1 << (j - 1))] = (memo[i][j - 1][k | (0b1 << (j - 1))] + memo[i - 1][j][k]) % 1000000000U;
                    memo[i][j + 1][k | (0b1 << (j + 1))] = (memo[i][j + 1][k | (0b1 << (j + 1))] + memo[i - 1][j][k]) % 1000000000U;

                }
        }

        for (u32 k = 0; k < 0b10000000000; k++) if(memo[i - 1][9][k]) memo[i][8][k | 0b0100000000] = (memo[i][8][k | 0b0100000000] + memo[i - 1][9][k]) % 1000000000U;
    }

    for(u32 j = 0; j < 10; j++) result = (result + memo[N][j][0b1111111111]) % 1000000000U;

    printf("%u\n", result);
}