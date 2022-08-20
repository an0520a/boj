#include <stdio.h>
#include<memory.h>

typedef unsigned int u32;

bool memo[101][1001] = { false };

int main()
{
    u32 N, S, M;
    u32 arr[101];

    scanf(" %u %u %u", &N, &S, &M);
    for(u32 i = 1; i <= N; i++) scanf(" %u", arr + i);

    memo[0][S] = true;

    for (u32 i = 1; i <= N; i++)
    {
        for (u32 j = 0; j <= 1000; j++)
        {
            if(memo[i - 1][j] == true)
            {
                if(arr[i] <= j) memo[i][j - arr[i]] = true;
                if(j + arr[i] <= M) memo[i][j + arr[i]] = true;
            }
        }
    }

    for (int i = M; i >= 0; i--)
    {
        if(memo[N][i])
        {
            printf("%u\n", i);
            return 0;
        }
    }

    printf("-1\n");
}