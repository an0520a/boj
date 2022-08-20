#include <stdio.h>

typedef unsigned int u32;
typedef unsigned long long u64;

u64 getPadovan(u64 n);

int main()
{
    u32 TC = 0;
    scanf(" %u", &TC);

    while (TC--)
    {
        u32 n;
        scanf(" %u", &n);
        printf("%llu\n", getPadovan(n));
    }
}

u64 getPadovan(u64 n)
{
    static u64 dp[101] = { 0, 1, 1, 1 };

    if (dp[n] != 0) return dp[n];
    else return dp[n] = getPadovan(n - 3) + getPadovan(n - 2);
}