#include <cstdio>
#include <malloc.h>
#include <memory.h>

typedef unsigned short u16;
typedef unsigned int u32;

int main()
{
    u32 N;
    auto max = [](const u32& x, const u32& y)->const u32&{ return (x > y)? x : y; };
    auto min = [](const u32& x, const u32& y)->const u32&{ return (x < y)? x : y; };
    u32 max_a, max_b, max_c;
    u32 min_a, min_b, min_c;

    scanf(" %u", &N);

    scanf(" %u %u %u", &max_a, &max_b, &max_c);

    min_a = max_a, min_b = max_b, min_c = max_c;

    for (size_t i = 1; i < N; i++)
    {
        u32 tmp_a, tmp_b, tmp_c;
        u32 next_a, next_b, next_c;

        scanf(" %u %u %u", &tmp_a, &tmp_b, &tmp_c);

        next_a = max(max_a, max_b) + tmp_a;
        next_b = max(max(max_a, max_b), max_c) + tmp_b;
        next_c = max(max_b, max_c) + tmp_c;

        max_a = next_a, max_b = next_b, max_c = next_c;

        next_a = min(min_a, min_b) + tmp_a;
        next_b = min(min(min_a, min_b), min_c) + tmp_b;
        next_c = min(min_b, min_c) + tmp_c;

        min_a = next_a, min_b = next_b, min_c = next_c;
    }

    printf("%u %u\n", max(max(max_a, max_b), max_c), min(min(min_a, min_b), min_c));
}