#include <iostream>

typedef unsigned int u32;

using namespace std;

int main()
{
    u32 n;
    u32 max_sum = 0;
    auto max = [](const u32& a, const u32& b)->const u32&{ return ((a > b)? a : b); };
    scanf(" %u", &n);

    u32* odd_arr = new u32[n];
    u32* even_arr = new u32[n];

    scanf(" %u", odd_arr);

    for (u32 i = 2; i <= n; i++)
    {
        if (i % 2 == 0)
        {
            u32 end = i - 1;
            u32 tmp;
            scanf(" %u", &tmp);
            even_arr[0] = tmp + odd_arr[0];

            for (u32 j = 1; j < end; j++)
            {
                scanf(" %u", &tmp);
                even_arr[j] = tmp + max(odd_arr[j - 1], odd_arr[j]);
            }

            scanf(" %u", &tmp);
            even_arr[end] = tmp + odd_arr[end - 1];
        }
        else
        {
            u32 end = i - 1;
            u32 tmp;
            scanf(" %u", &tmp);
            odd_arr[0] = tmp + even_arr[0];

            for (u32 j = 1; j < end; j++)
            {
                scanf(" %u", &tmp);
                odd_arr[j] = tmp + max(even_arr[j - 1], even_arr[j]);
            }

            scanf(" %u", &tmp);
            odd_arr[end] = tmp + even_arr[end - 1];
        }
    }

    if (n % 2 == 0)
    {   
        for (u32 i = 0; i < n; i++)
        {
            max_sum = max(max_sum, even_arr[i]);
        }
    }
    else
    {
        for (u32 i = 0; i < n; i++)
        {
            max_sum = max(max_sum, odd_arr[i]);
        }
    }

    printf("%u\n", max_sum);

    delete[] odd_arr;
    delete[] even_arr;
}