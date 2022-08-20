#include <stdio.h>
#include <algorithm>

typedef unsigned int u32;

void NM(u32 N, u32 M, u32* num);
void NM_computed(u32 S, u32 N, u32 M, u32* num, u32* arr, u32 arrLen, u32 index);
int cmp(u32 a, u32 b);

int main()
{
    u32 N, M;
    scanf(" %u %u", &N, &M);

    u32* num = new u32[N + 1];

    for (u32 i = 1; i <= N; i++) scanf(" %u", num + i);

    std::sort(num + 1, num + N + 1);

    NM(N, M, num);
}

int cmp(u32 a, u32 b) { return a > b; }

void NM(u32 N, u32 M, u32* num)
{
    u32* arr = new u32[M];

    NM_computed(1, N, M, num, arr, M, 0);
}

void NM_computed(u32 S, u32 N, u32 M, u32* num, u32* arr, u32 arrLen, u32 index)
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
            arr[index] = num[i];
            NM_computed(i, N, M - 1, num, arr, arrLen, index + 1);
        }
    }
}