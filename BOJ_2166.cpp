#include <stdio.h>
#include <stdlib.h>

typedef unsigned int u32;
typedef unsigned long long u64;
typedef long long i64;

typedef struct _point
{
    int x;
    int y;
} point;

int main()
{
    u32 N;
    i64 sum1 = 0;
    i64 sum2 = 0;
    
    scanf(" %u", &N);

    point* arr = (point *)malloc(N * sizeof(point));

    for (u32 i = 0; i < N; i++)
    {
        scanf(" %d %d", &arr[i].x, &arr[i].y);
    }

    for (u32 i = 0; i < N; i++)
    {
        sum1 += (i64)arr[i].x * arr[(i + 1) % N].y;
        sum2 += (i64)arr[(i + 1) % N].x * arr[i].y;
    }

    printf("%.1lf\n", (double)((sum1 > sum2)? sum1 - sum2 : sum2 - sum1)/2.0);

    free(arr);
}
