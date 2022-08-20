#include <stdio.h>

typedef unsigned int u32;

int main()
{
    u32 N;
    scanf(" %u", &N);

    printf("%u\n", N / 5 + N / 25 + N / 125);
}