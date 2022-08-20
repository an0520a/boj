#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef unsigned int u32;
typedef unsigned long long u64;

int main()
{
    u64 N, M;
    u64 max = 0, min = 0xFFFFFFFFFFFFFFFF;
    scanf(" %llu %llu", &N, &M);

    u64* arr = (u64 *)malloc(N * sizeof(u64));

    for (u64 i = 0; i < N; i++)
    {
        scanf(" %llu", arr + i);
        max = (max > arr[i])? max : arr[i];
        min = (min < arr[i])? min : arr[i];
    }

    u64 front = (((((max > M)? max - M : 0) > min)? max - M : min) & 0x8000000000000000)? min : 0;
    u64 back = max;
    u64 middle;

    while(front <= back)
    {
        middle = (front + back) / 2;
        u64 sum = 0;
        for(u64 i = 0; i < N; i++) { sum += (middle < arr[i])? arr[i] - middle : 0; }

        if      (sum > M) { front = middle + 1; }
        else if (sum < M) { back  = middle - 1; }
        else              { break; }
    }

    if(front > back)
    {
        u64 sum = 0;
        for(u64 i = 0; i < N; i++) { sum += (middle < arr[i])? arr[i] - middle : 0; }

        if(sum > M)
        {
            while(sum > M)
            {
                middle++;
                sum = 0;
                for(u64 i = 0; i < N; i++) { sum += (middle < arr[i])? arr[i] - middle : 0; }
            }

            middle--;
        }
        else if (sum < M)
        {
            while(sum < M)
            {
                middle--;
                sum = 0;
                for(u64 i = 0; i < N; i++) { sum += (middle < arr[i])? arr[i] - middle : 0; }
            }
        }
    }

    printf("%llu\n", middle);

    free(arr);
}