#include <stdio.h>

typedef unsigned int u32;

u32 getNum(u32 x, u32 y);

int main()
{
    u32 n, m;
    
    scanf(" %u %u", &n, &m);

    printf("%u\n", getNum(n, m));
}

u32 getNum(u32 x, u32 y)
{
    static u32 memo[1001][1001] = { { 0 }, { 0, 1 } };

    if (memo[x][y]) return memo[x][y];
    else
    {
        u32 sum = 0;

        if(x!= 1 && y != 1) sum = getNum(x - 1, y - 1);
        if(x != 1) sum += getNum(x - 1, y);
        if(y != 1) sum += getNum(x, y - 1);

        return memo[x][y] = sum % 1000000007;
    }
}