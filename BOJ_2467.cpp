#include <stdio.h>
#include <malloc.h>
#include <algorithm>

typedef unsigned int u32;

int main()
{
    u32 N;
    int* arr;

    scanf(" %d", &N);

    arr = (int *)malloc(N * sizeof (int));

    for (int i = 0; i < N; i++) scanf(" %u", arr + i);

    std::sort(arr, arr + N, [](const int& x, const int& y)->bool{ return x < y; });

    int *p = arr;
    int *q = arr + N - 1;
    int bestNum1 = *p;
    int bestNum2 = *q;

    while(p < q)
    {
        if(abs(*p + *q) < abs(bestNum1 + bestNum2))
        {
            bestNum1 = *p;
            bestNum2 = *q;
        }

        if(*p + *q < 0) p++;
        else            q--; 
    }

    printf(" %d %d", bestNum1, bestNum2);

    free(arr);
}