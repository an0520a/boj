#include <stdio.h>

typedef unsigned int u32;

void hanoi(u32 org, u32 to, u32 dst, u32 n);

int main()
{
    u32 N, K = 1;
    scanf(" %u", &N);

    for (u32 i = 2; i <= N; i++)
    {
        K = 2 * K + 1;
    }

    printf("%u\n", K);
    hanoi(1, 2, 3, N);

}

void hanoi(u32 org, u32 to, u32 dst, u32 n)
{
    if (n == 1) printf("%u %u\n", org, dst);
    else
    {
        hanoi(org, dst, to, n - 1);
        printf("%u %u\n", org, dst);
        hanoi(to, org, dst, n - 1);
    }
}