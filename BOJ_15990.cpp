#include <stdio.h>

typedef unsigned int u32;

u32 OneTwoThreePlus(u32 n, u32 idx = 0);

int main()
{
    u32 n;
    scanf(" %u", &n);

    for (u32 i = 0; i < n; i++)
    {
        u32 m;
        scanf(" %u", &m);

        printf("%u\n", OneTwoThreePlus(m, 0));
    }
}

u32 OneTwoThreePlus(u32 n, u32 idx)
{
    static u32 memo[100001][4] = { {0, 0, 0, 0}, { 1, 1, 0, 0}, {1, 0, 1, 0}, { 3, 1, 1, 1} };

    if (memo[n][0])
    {
        return memo[n][idx];
    }
    else
    {
        memo[n][1] = (OneTwoThreePlus(n - 1, 2) + OneTwoThreePlus(n - 1, 3)) % 1000000009;
        memo[n][2] = (OneTwoThreePlus(n - 2, 1) + OneTwoThreePlus(n - 2, 3)) % 1000000009;
        memo[n][3] = (OneTwoThreePlus(n - 3, 1) + OneTwoThreePlus(n - 3, 2)) % 1000000009;

        memo[n][0] = (memo[n][1] + memo[n][2] + memo[n][3]) % 1000000009;

        return memo[n][idx];
    }
}