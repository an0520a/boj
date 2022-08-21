#include <stdio.h>

typedef unsigned short u16;
typedef unsigned int u32;

u16 getNum(u32 n, u32 idx);

int main()
{
    u32 N;
    scanf(" %u", &N);

    printf("%hu\n", (getNum(N, 0) + getNum(N, 1) + getNum(N, 2)) % 9901);
}

u16 getNum(u32 n, u32 idx)
{
    static u16 memo[100001][3] { {0, 0, 0}, {1, 1, 1} };

    if(memo[n][0]) return memo[n][idx];
    else
    {
        memo[n][0] = (getNum(n - 1, 0) + getNum(n - 1, 1) + getNum(n - 1, 2)) % 9901;
        memo[n][1] = (getNum(n - 1, 0) + getNum(n - 1, 2)) % 9901;
        memo[n][2] = (getNum(n - 1, 0) + getNum(n - 1, 1)) % 9901;

        return memo[n][idx];
    }
}