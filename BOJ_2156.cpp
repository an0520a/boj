#include <stdio.h>
#include <malloc.h>

typedef unsigned int u32;

u32 getMax(u32* arr, u32 n);

int main()
{
    u32 N;
    u32* arr;

    scanf(" %u", &N);
    arr = (u32 *)malloc(N * sizeof(u32));

    for (u32 i = 0; i < N; i++) scanf(" %u", arr + i);

    printf("%u\n", getMax(arr, N - 1));
}

u32 getMax(u32* arr, u32 n)
{
    static u32 memo[10001] = { 0 };

    if(memo[n]) return memo[n];
    else if(n == 0) return memo[0] = arr[0];
    else if(n == 1) return memo[1] = arr[0] + arr[1];
    else if(n == 2)
    {
        u32 a = arr[0] + arr[1];
        u32 b = arr[0] + arr[2];
        u32 c = arr[1] + arr[2];

        return memo[n] = (((a > b)? a : b) > c)? ((a > b)? a : b) : c;
    }
    else
    {
        u32 a = getMax(arr, n - 3) + arr[n - 1] + arr[n];
        u32 b = getMax(arr, n - 2) + arr[n];
        u32 c = getMax(arr, n - 1);

        return memo[n] = ((((a > b)? a : b) > c)? ((a > b)? a : b) : c);
    }
}