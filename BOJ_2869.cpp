#include <stdio.h>

typedef unsigned int u32;

int main()
{
    u32 A, B, V;
    scanf(" %u %u %u", &A, &B ,&V);

    printf("%u\n", (V-A) / (A - B) + 1 + (((V - A) % (A - B))? 1 : 0));
}