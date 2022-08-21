#include <stdio.h>

typedef unsigned int u32;

u32 tile(u32 n);
u32 tile_n(u32 n);

int main()
{
    u32 n;
    scanf(" %u", &n);

    printf("%u\n", tile_n(n));
}

u32 tile(u32 n)
{
    static u32 memo[1001] = { 0, 1, 3 };

    if (memo[n]) return memo[n];
    else return memo[n] = (tile(n - 1) + tile(n - 2) * 2) % 10007;
}

u32 tile_n(u32 n)
{
    switch (n)
    {
    case 0:
        return 0;
        break;

    case 1:
        return 1;
        break;

    case 2:
        return 3;
        break;
    
    default:
        return (tile_n(n - 1) + tile_n(n - 2) * 2) % 10007;
        break;
    }
}