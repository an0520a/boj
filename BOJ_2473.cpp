#include <stdio.h>
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

    int bestNum1 = *arr;
    int bestNumM = *(arr + 1);
    int bestNum2 = *(arr + N - 1);

    for (int* m = arr + 1; m < arr + N - 1; m++)
    {
        int *p = arr;
        int *q = arr + N - 1;

        while(p < m && q > m)
        {
            long long preVal = (long long)*p + *m + *q;
            long long bestVal = (long long)bestNum1 + bestNumM + bestNum2;

            if(abs(preVal) < abs(bestVal))
            {
                bestNum1 = *p;
                bestNumM = *m;
                bestNum2 = *q;
            }

            if((long long)*p + *m + *q < 0)
            {
                p++;
            }
            else
            {
                q--;
            }
        }
    }

    printf(" %d %d %d", bestNum1, bestNumM, bestNum2);

    free(arr);
}