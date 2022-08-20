#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <memory.h>

typedef unsigned int u32;

int main()
{
    u32 N;
    u32 result = 0;
    u32 size = 0;
    u32 capacity = 16;
    u32* prime_arr = (u32 *)malloc(capacity * sizeof(u32));
    bool* field;

    scanf(" %u", &N);

    field = (bool *)malloc((N + 1) * sizeof(bool));
    memset(field, true, (N + 1) * sizeof(bool));

    for (u32 i = 2; i * i <= N; i++)
    {
        if(field[i] == true)
        {
            for (u32 j = 2; i * j <= N; j++)
            {
                field[i * j] = false;
            }
        }
    }

    for (u32 i = 2; i <= N; i++)
    {
        if(field[i] == true)
        {
            prime_arr[size] = i;
            size++;

            if(size == capacity)
            {
                u32* tmp;
                if(!(tmp = (u32 *)realloc(prime_arr, 2 * capacity * sizeof(u32)))) return -1;
                capacity *= 2;
                prime_arr = tmp;
            }
        }
    }

    u32* p = prime_arr;
    u32* q = prime_arr;
    u32 sum = 0;

    while(q != prime_arr + size)
    {
        if(sum >= N) sum -= *p, p++;
        else         sum += *q, q++;

        if(sum == N) result++;
    }

    while(sum >= N)
    {
        sum -= *p, p++;

        if(sum == N) result++;
    }

    printf("%u\n", result);

    free(field);
    free(prime_arr);
}