#include <stdio.h>
#include <malloc.h>

typedef unsigned short     u16;
typedef unsigned int       u32;

int main()
{
    u32 N;
    u32 max = 0;
    u16* arr;
    u16* len;

    scanf(" %u", &N);

    arr = (u16*)malloc(N * sizeof(u16));
    len = (u16*)calloc(N, sizeof(u16));

    scanf(" %hu", arr);
    len[0] = 1;
    for (u32 i = 1; i < N; i++)
    {
        scanf(" %hu", arr + i);
        len[i] = (arr[i] > arr[0])? 1 : 0;
    }

    for (u32 i = 1; i < N; i++)
    {
        len[i]++;

        for (u32 j = i + 1; j < N; j++)
        {
            len[j] = ((arr[j] > arr[i]) && len[i] > len[j])? len[i] : len[j];
        }
    }

    for (u32 i = 0; i < N; i++)
    {
        max = (len[i] > max)? len[i] : max;
    }

    printf("%u\n", max);
}