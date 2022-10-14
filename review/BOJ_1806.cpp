#include <iostream>

typedef unsigned int u32;

int main()
{
    u32 N, S;
    u32 *arr = nullptr;
    size_t subtotal_len = 0xFFFFFFFF;

    std::ios_base::sync_with_stdio(false);

    std::cin >> N >> S;

    arr = new u32[N];
    for (u32 i = 0; i < N; i++)
    {
        std::cin >> arr[i];
    }

    u32* begin = arr;
    u32* end = arr + N;

    u32 *p = arr, *q = arr;
    u32 sum = 0;

    while(q < end)
    {
        if (sum < S)
        {
            sum += *q;
            q++;
        }

        if (sum >= S)
        {
            subtotal_len = std::min(subtotal_len, (size_t)(q - p));
            sum -= *p;
            p++;
        }
    }

    while (sum >= S)
    {
        subtotal_len = std::min(subtotal_len, (size_t)(q - p));
        sum -= *p;
        p++;
    }

    delete[] arr;

    if (subtotal_len != 0xFFFFFFFF) std::cout << subtotal_len << std::endl;
    else                            std::cout << 0 << std::endl;
}