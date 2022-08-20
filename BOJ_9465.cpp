#include <stdio.h>
#include <stdlib.h>

typedef unsigned int u32;

u32 getScore(u32 (*arr)[100000], u32 N);

int main()
{
    u32 TC;
    u32 arr[2][100000];
    scanf(" %u", &TC);

    while(TC--)
    {
        u32 N;
        scanf(" %u", &N);

        for(u32 i = 0; i < N; i++)
        {
            scanf(" %u", &arr[0][i]);
        }
        for(u32 i = 0; i < N; i++)
        {
            scanf(" %u", &arr[1][i]);
        }

        printf("%u\n", getScore(arr, N));
    }
}

u32 getScore(u32 (*arr)[100000], u32 N)
{
    const static auto max = [](const u32& A, const u32& B)->u32{ return (A > B)? A : B; };

    if      (N == 1) return max(arr[0][0], arr[1][0]);
    else
    {
        u32 result, bb0, bb1, b0, b1, tmp0, tmp1;

        bb0 = arr[0][0];
        bb1 = arr[1][0];

        b0 = bb1 + arr[0][1];
        b1 = bb0 + arr[1][1];
        
        for (u32 i = 2; i < N; i++)
        {
            tmp0 = max(b1, bb1) + arr[0][i];
            tmp1 = max(b0, bb0) + arr[1][i];

            bb0 = b0;
            bb1 = b1;
            b0 = tmp0;
            b1 = tmp1;
        }

        result = max(b0, b1);

        return result;
    }
}