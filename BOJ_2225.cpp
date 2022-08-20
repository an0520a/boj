#include <stdio.h>

typedef unsigned int u32;

u32 getCount(u32 N, u32 K);

int main()
{
    u32 N, K;
    scanf(" %u %u", &N, &K);

    printf("%u\n", getCount(N, K));
}

u32 getCount(u32 N, u32 K)
{
    static u32 memo[201][201] = { 0 };

    if(memo[N][K]) return memo[N][K];
    else if(N == 0) return 1;
    else if(K == 1) return 1;
    else
    {
        u32 sum = 0;

        for(u32 i = 0; i <= N; i++)
        {
            sum = (sum + getCount(N - i, K - 1)) % 1000000000;
        }

        return memo[N][K] = sum;
    }
}