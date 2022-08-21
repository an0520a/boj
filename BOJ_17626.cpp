#include <stdio.h>
#include <stdbool.h>

typedef unsigned int u32;

u32 getForSquares(const u32 n);

int main()
{
    u32 n;
    scanf(" %u", &n);
    printf("%u\n", getForSquares(n));
}

u32 getForSquares(const u32 n)
{
    static bool flag = true;
    static u32 memo[50001] = { 0 , 1};

    if (flag)
    {
        for (u32 i = 1; i * i <= 50000; i++)
        {
            memo[i * i] = 1;
        }
        flag = false;
    }
    
    if (n == 0) return 0;
    if (memo[n] != 0)
    {
        return memo[n];
    }
    else
    {
        u32 min = 0xFFFFFFFF;

        for (u32 i = 1; i * i <= n; i++)
        {
            u32 sum = getForSquares(i * i) + getForSquares(n - (i * i));
            min = (min < sum)? min : sum;
        }

        return memo[n] = min;
    }
}