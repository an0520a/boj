#include <stdio.h>
#include <malloc.h>

typedef unsigned int u32;

int main()
{
    u32 N, M;
    u32* num;
    u32* end;
    u32* p, *q;
    u32 sum = 0;
    u32 count = 0;

    scanf(" %u %u", &N, &M);

    num = (u32 *)malloc(N * sizeof(u32));
    end = num + N;

    for (u32 i = 0; i < N; i++) scanf(" %u", num + i);

    p = num, q = num + 1, sum += num[0];
    
    while (q != end)
    {
        if (sum == M) count++;

        if (sum >= M) sum -= *p, p++;
        else sum += *q, q++;
    }

    while (sum >= M)
    {
        if (sum == M) count++;
        sum -= *p, p++;
    }

    printf("%u\n", count);

    free(num);
}