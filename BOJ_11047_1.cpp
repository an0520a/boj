#include <stdio.h>

typedef unsigned int u32;

int main()
{
    u32 N, K;
    u32 result = 0;
    u32* coin;
    scanf(" %u %u", &N, &K);

    coin = new u32[N];

    for (u32 i = 0; i < N; i++)
    {
        scanf(" %u", coin + i);
    }

    for (int i = N - 1; K != 0; i--)
    {
        if (coin[i] <= K)
        {
            u32 tmp = K / coin[i];
            K -= tmp * coin[i];
            result += tmp;
        }
    }

    printf("%u\n", result);

    delete coin;
}