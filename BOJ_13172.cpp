#include <stdio.h>

typedef unsigned int u32;
typedef unsigned long long u64;

u32 pow(u32 a, u32 b, u32 m);
u32 gcd(u32 a, u32 b);
u32 inverse(u32 a, u32 p);

int main()
{
    u32 M;
    u32 result = 0;

    scanf(" %u", &M);

    while (M--)
    {
        u32 numerator;
        u32 denominator;
        u32 g;

        scanf(" %u %u", &denominator, &numerator);
        g = gcd(numerator, denominator);

        numerator /= g;
        denominator /= g;

        result = ((u64)result + (u64)numerator * inverse(denominator, 1000000007)) % 1000000007;
    };

    printf("%u\n", result);
}

// p가 소수가 아님은 계산하지 않음.
u32 inverse(u32 a, u32 p)
{
    return pow(a, p - 2, p);
}

u32 pow(u32 a, u32 b, u32 m)
{
    u32 ret = a;
    u32 result = 1;

    do
    {
        if (b & 1) result = (u64)result * ret % m;
        ret = (u64)ret * ret % m;
    } while (b >>= 1);

    return result;
}

u32 gcd(u32 a, u32 b)
{
    u32 r;

    while (b != 0)
    {
        r = a % b;
        a = b;
        b = r;
    }

    return a;
}