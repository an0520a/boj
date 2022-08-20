#include <stdio.h>

typedef unsigned long long u64;
typedef unsigned int u32;

int main()
{
    u32 N, K;
    scanf(" %u", &N);

    K = (N + 1) / 2;

    if (N & 1)
    {
        for (u32 i = 0; i < N / 2; i++)
        {
            printf("%u ", K + i);
            printf("%u ", N - (K + i));
        }
        printf("%u ", N);
    }
    else
    {
        printf("%u ", K);

        for (u32 i = 1; i < N / 2; i++)
        {
            printf("%u ", K + i);
            printf("%u ", N - (K + i));
        }

        printf("%u ", N);
    }
}