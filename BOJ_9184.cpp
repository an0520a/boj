#include <stdio.h>

typedef unsigned int u32;
typedef unsigned long long u64;
typedef long long i64;

int w(int a, int b, int c);

int main()
{
    int a, b, c;

    while (true)
    {
        scanf(" %d %d %d", &a, &b, &c);

        if(a == -1 && b == -1 && c == -1) return 0;
        else                              printf("w(%d, %d, %d) = %d\n", a, b, c, w(a, b, c));
    }
}

int w(int a, int b, int c)
{
    static int memo[21][21][21] = { 0 };

    if     (a <= 0 || b <= 0 || c <= 0) return 1;
    else if(a > 20 || b > 20 || c > 20) return w(20, 20, 20);
    else if(memo[a][b][c])              return memo[a][b][c];
    else if(a < b && b < c)             return memo[a][b][c] = w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c);
    else                                return memo[a][b][c] = w(a - 1, b, c) + w(a - 1, b - 1, c) + w(a - 1, b, c - 1) - w(a - 1, b - 1, c - 1);
}