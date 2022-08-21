#include <stdio.h>

typedef unsigned int u32;

u32 getPerson(u32 k, u32 n);

int main()
{
    u32 T, n, k;

    scanf(" %u", &T);

    while(T--)
    {
        scanf(" %u %u", &k, &n);

        printf("%u\n", getPerson(k, n));
    }
}

u32 getPerson(u32 k, u32 n)
{
    static u32 arr[15][15] = { { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14} , 0 };

    if(arr[k][n]) return arr[k][n];
    else
    {
        u32 tmp = 0;
        for(u32 i = n; i != 0; i--) tmp += getPerson(k - 1, i);
        
        return arr[k][n] = tmp;
    }
}