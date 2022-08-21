#include <stdio.h>
#include <malloc.h>
#include <algorithm>

typedef unsigned int u32;
typedef unsigned long long u64;
typedef long long i64;

using namespace std;

int main()
{
    u32 N;
    int* arr;
    int * p, * q;
    int * s, * e;
    i64 opt;
    i64 sum = 0;

    scanf(" %u", &N);

    arr = (int *)malloc(N * sizeof(int));

    for (u32 i = 0; i < N; i++) scanf(" %d", arr + i);
    sort(arr, arr + N);

    p = arr, q = arr + N - 1;
    sum = *p + *q;
    s = p, e = q;
    opt = sum;

    while(p != q)
    {
        if (abs(sum) < abs(opt))
        {
            opt = sum;
            s = p;
            e = q;
        }

        if (sum >= 0) q--;
        else          p++;

        sum = *p + *q;
    }

    printf("%d %d", *s, *e);

    free(arr);
}