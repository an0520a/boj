#include <stdio.h>
#include <malloc.h>

typedef unsigned int u32;

int main()
{
    u32 N, M;
    scanf(" %u %u", &N, &M);

    u32 (*arr)[N + 1] = (u32 (*)[N + 1])calloc((N + 1) * (N + 1), sizeof(u32));
    for (u32 i = 1; i <= N; i++)
    {
        for (u32 j = 1; j <= N; j++)
        {
            scanf(" %u", arr[i] + j);
            arr[i][j] += arr[i - 1][j];
        }
    }

    for (u32 i = 1; i <= N; i++)
    {
        for(u32 j = 2; j <= N; j++)
        {
            arr[i][j] += arr[i][j - 1];
        }
    }

    while (M--)
    {
        u32 x1, y1, x2, y2;
        u32 size1 = 0, size2 = 0;

        scanf(" %u %u %u %u", &y1, &x1, &y2, &x2);

        size1 += (arr[y1 - 1][x2] - arr[y1 - 1][x1 - 1]);
        size2 += (arr[y2][x2]     - arr[y2][x1 - 1]    );
        printf("%u\n", size2 - size1);
    }

    free(arr);
}