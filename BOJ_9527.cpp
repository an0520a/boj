#include <cstdio>

typedef unsigned int u32;
typedef unsigned long long u64;

u64 pow(u64 a, u64 b);
u64 getSizeI(u64 A, u64 i);
u64 getSizeI(u64 A, u64 B, u64 i);

int main()
{
    u64 A, B;
    u64 sum = 0;

    scanf(" %llu %llu", &A, &B);

    for(u32 i = 0; i < 63; i++) sum += getSizeI(A, B, i);

    printf("%llu\n", sum);
}

u64 pow(u64 a, u64 b)
{
    u64 ret = 1;

    do
    {
        if(b & 1) ret = (__uint128_t)ret * (__uint128_t)a;
        a = (__uint128_t)a * (__uint128_t)a;
    } while (b >>= 1);

    return ret;
}

u64 getSizeI(u64 A, u64 B, u64 i)
{
    return getSizeI(B, i) - getSizeI(A - 1, i);
}

u64 getSizeI(u64 A, u64 i)
{
    u64 m = pow(2, i + 1);
    return (A / m) * (m / 2) + ((A % m > (m / 2 - 1))? A % m - (m / 2 - 1) : 0);
}