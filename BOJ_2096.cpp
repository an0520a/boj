#include <stdio.h>

typedef unsigned int u32;

int main()
{
    u32 a_max, b_max, c_max;
    u32 a_max_ = 0, b_max_ = 0, c_max_ = 0;
    u32 a_min, b_min, c_min;
    u32 a_min_ = 0, b_min_ = 0, c_min_ = 0;
    u32 N;
    auto max = [](const u32& a, const u32& b)->const u32&{ return ((a > b)? a : b); };
    auto min = [](const u32& a, const u32& b)->const u32&{ return ((a < b)? a : b); };

    scanf(" %u", &N);

    while(N--)
    {
        scanf(" %u %u %u", &a_max, &b_max, &c_max);
        a_min = a_max, b_min = b_max, c_min = c_max;

        a_max += max(a_max_, b_max_);
        b_max += max(max(a_max_, b_max_), c_max_);
        c_max += max(b_max_, c_max_);

        a_min += min(a_min_, b_min_);
        b_min += min(min(a_min_, b_min_), c_min_);
        c_min += min(b_min_, c_min_);

        a_max_ = a_max; 
        b_max_ = b_max;
        c_max_ = c_max;

        a_min_ = a_min;
        b_min_ = b_min;
        c_min_ = c_min;
    }

    printf("%u %u\n", max(max(a_max, b_max), c_max), min(min(a_min, b_min), c_min));

}