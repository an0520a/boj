#include <cstdio>
#include <memory.h>

typedef unsigned int u32;
typedef unsigned long long u64;

constexpr void SumNum(u64* dst, u64 weight, u64 num);
u64* getCount(u64 num);

int main()
{
    u64 N;
    u64* count;

    scanf(" %llu", &N);

    count = getCount(N);

    for (u64 i = 0; i < 10; i++) printf("%llu ", count[i]);
    printf("\n");

    delete[] count;
}

constexpr void SumNum(u64* dst, u64 weight, u64 num)
{
    while (num)
    {
        dst[num % 10] += weight;
        num /= 10;
    }
}

u64* getCount(u64 num)
{
    u64* dst = new u64[10];
    u32 begin = 1;
    u32 end = num;
    u32 w = 1;
    u64 sub[10] = { 0 };

    while (end)
    {
        while(end >= begin && begin % 10 != 0)
        {
            SumNum(dst, w, begin);
            begin++;
        }

        while(end >= begin && end % 10 != 9)
        {
            SumNum(dst, w, end);
            end--;
        }

        if (end < begin) break;

        for (u64 i = 0; i < 10; i++) dst[i] += ((end / 10) - (begin / 10) + 1) * w;

        begin /= 10;
        end /= 10;
        w *= 10;
    }

    return dst;
}
