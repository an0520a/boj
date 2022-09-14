#include <iostream>

typedef unsigned int u32;
typedef unsigned long long u64;

template <u32 mod> u32 ModInv(u32 x);
template <u32 mod> u32 ModPow(u32 x, u32 y);
u32 gcd(u32 x, u32 y);

int main()
{
    std::ios_base::sync_with_stdio(false);

    size_t M;
    u32 result = 0;
    
    std::cin >> M;

    for (size_t i = 0; i < M; i++)
    {
        u32 numerator;
        u32 denominator;
        u32 g;

        std::cin >> denominator >> numerator;

        g = gcd(numerator, denominator);

        
        g = gcd(numerator, denominator);

        result = ((u64)result + (u64)numerator * (u64)ModInv<1000000007>(denominator)) % 1000000007ULL;
    }

    std::cout << result << std::endl;
}

template <u32 mod>
u32 ModInv(u32 x)
{
    return ModPow<mod>(x, mod - 2);
}

template <u32 mod>
u32 ModPow(u32 x, u32 y)
{
    u32 result = 1;

    do
    {
        if(y & 1) result = (u64)result * (u64)x % (u64)mod;
        x = (u64)x * (u64)x % (u64)mod;
    } while (y >>= 1);
    
    return result;
}

u32 gcd(u32 x, u32 y)
{
    while (y != 0)
    {
        u32 r = x % y;
        x = y;
        y = r;
    }

    return x;
}