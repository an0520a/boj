#include <stdio.h>
#include <malloc.h>

typedef unsigned int u32;

int main()
{
    u32 N;
    int* arr;
    int* S;
    int max;
    int min;
    
    scanf(" %u", &N);
    arr = (int *)malloc(N * sizeof(int));
    S = (int *)malloc(N * sizeof(int));

    int sum = 0;
    for (u32 i = 0; i < N; i++)
    {
        scanf(" %d", arr + i);
        S[i] = sum += arr[i];
    }

    max = S[0];
    min = 0;
    for (u32 i = 1; i < N; i++)
    {
        min = (min < S[i - 1])? min : S[i - 1];
        max = (max > S[i] - min)? max : S[i] - min;
    }

    printf("%d\n", max);

    free(arr);
    free(S);
}