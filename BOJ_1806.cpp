#include <stdio.h>
#include <malloc.h>

typedef unsigned short u16;
typedef unsigned int   u32;

int main()
{
    u32 N, M;
    u32* nums;
    u32 *p, *q;
    u32 *end;
    u32 sum = 0;
    u32 min = 0xFFFFFFFF;

    scanf(" %u %u", &N, &M);

    nums = (u32 *)malloc(N * sizeof(u32));

    for (u32 i = 0; i < N; i++) scanf(" %u", nums + i);

    p = nums;
    q = nums + 1;
    end = nums + N;
    sum = *p;

    while(q != end)
    {
        if(sum >= M)
        {
            min = (min <= q - p)? min : q - p;
        }

        if(sum >= M) sum -= *p, p++;
        else         sum += *q, q++;
    }

    while(sum >= M)
    {
        if(sum >= M)
        {
            min = (min <= q - p)? min : q - p;
        }

        sum -= *p, p++;
    }

    if (min == 0xFFFFFFFF) printf("0\n");
    else                   printf("%u\n", min);

    free(nums);
}