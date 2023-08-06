#include <cstdio>

int main()
{
    unsigned long long N;
    unsigned long long r, c;
    unsigned long long harf_line_size;
    unsigned long long harf_squre_size;
    size_t num = 0;

    scanf(" %llu", &N);
    scanf(" %llu %llu", &r, &c);

    harf_line_size = 1 << (N - 1);
    harf_squre_size = 1 << (2 * (N - 1));

    while (harf_line_size != 0)
    {
        if (r >= harf_line_size)
        {
            num += (harf_squre_size << 1);
            r -= harf_line_size;
        }

        if (c >= harf_line_size)
        {
            num += harf_squre_size;
            c -= harf_line_size;
        }

        harf_line_size >>= 1;
        harf_squre_size >>= 2;
    }

    printf("%lu\n", num);
}