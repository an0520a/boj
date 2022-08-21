#include <iostream>

typedef unsigned int u32;
typedef unsigned long long u64;
typedef __uint128_t u128;

u128 combination(u32 n, u32 r);

using namespace std;

int main()
{
    u32 n, r;
    scanf(" %u %u", &n, &r);

    char str[50] = { 0 };
    u128 result = combination(n, r);
    u64 ull_lim = 10000000000000000000ULL;
    u128 div = (u128)ull_lim * ull_lim;

    char* p = str;

    do
    {
        if(result / div) break;
    } while(div /= 10);

    do
    {
        *p = result / div + '0';
        result %= div;
        div /= 10;
        p++;
    } while(div);

    printf("%s\n", str);
}

u128 combination(u32 n, u32 r)
{
    static u128 arr[101][101] = { 0 };

    if   (arr[n][r]) return arr[n][r];
    if (r == 0) return 1;
    else if (n == r) return 1;
    else if (r == 1) return n;
    else             return arr[n][r] = combination(n - 1, r - 1) + combination(n - 1, r);
}
