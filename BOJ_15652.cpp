#include <stdio.h>
#include <malloc.h>

typedef unsigned int u32;

void NM(u32 N, u32 M);
void NM_computed(u32 S, u32 N, u32 M, u32* arr, u32 arrLen, u32 index);

int main()
{
    u32 N, M;
    scanf(" %u %u", &N, &M);

    NM(N, M);
}

void NM(u32 N, u32 M)
{
    u32* arr = new u32[M];

    NM_computed(1, N, M, arr, M, 0);
}

void NM_computed(u32 S, u32 N, u32 M, u32* arr, u32 arrLen, u32 index)
{
    if (M == 0)
    {
        for (u32 i = 0; i < arrLen; i++)
            printf("%u ", arr[i]);
        printf("\n");
    }
    else
    {
        for (u32 i = S; i <= N; i++)
        {
            arr[index] = i;
            NM_computed(i, N, M - 1, arr, arrLen, index + 1);
        }
    }
}