#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <vector>

typedef unsigned int u32;
typedef unsigned long long u64;
typedef long long i64;

using namespace std;

int main()
{
    u32 N, M;
    u32 org = 100;
    u32 result = 0;
    bool button[10] = { true, true, true, true, true, true, true, true, true, true };

    scanf(" %u", &N);
    scanf(" %u", &M);

    while(M--)
    {
        u32 tmp;
        scanf(" %u", &tmp);
        button[tmp] = false;
    }

    auto check =
    [&button](u32 n)->bool
    {
        do
        {
            if(!button[n % 10]) return 0;
            n /= 10;
        } while(n);

        return 1;
    };

    auto sub_abs = [](const u32& a, const u32& b)->u32{ return (a > b)? a - b : b - a; };

    if(!(button[0] || button[1] || button[2] || button[3] || button[4] || button[5] || button[6] || button[7] || button[8] || button[9]))
    {
        printf("%u\n", sub_abs(org, N));
        return 0;
    }

    for (u32 i = 0, val = sub_abs(org, N); i < 888890; i++)
    {
        if(check(i) && (sub_abs(i, N) < val))
        {
            val = sub_abs(i, N);
            org = i;
        }
    }

    u32 tmp = org;

    do
    {
        result++;
    } while (tmp /= 10);

    result += sub_abs(org, N);
    result = (result < sub_abs(100, N))? result : sub_abs(100, N);

    printf("%u\n", result);
}