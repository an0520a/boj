#include <stdio.h>

typedef unsigned int u32;

u32 max_len(u32* arr, u32 len);
u32 max_len_computed(u32 index, u32* arr, u32* len_arr, bool* computed, u32 len);

int main()
{
    u32 N;
    scanf(" %u", &N);
    
    u32* arr = new u32[N];

    for(u32 i = 0; i < N; i++) scanf(" %u", arr + i);

    printf("%u\n", max_len(arr, N));
}

u32 max_len(u32* arr, u32 len)
{
    u32* len_arr = new u32[len];
    bool* computed = new bool[len]{ false };
    u32 max = 1;

    for(u32 i = 0; i < len; i++) max_len_computed(i, arr, len_arr, computed, len);

    for (u32 i = 0; i < len; i++)
    {
        max = (len_arr[i] > max)? len_arr[i] : max;
    }

    delete[] len_arr;
    delete[] computed;

    return max;
}

u32 max_len_computed(u32 index, u32* arr, u32* len_arr, bool* computed, u32 len)
{
    if (computed[index]) return len_arr[index];
    else
    {
        u32 max = 1;

        for (u32 i = index + 1; i < len; i++)
        {
            if(arr[i] > arr[index])
            {
                u32 tmp = max_len_computed(i, arr, len_arr, computed, len) + 1;
                max = (tmp > max)? tmp : max;
            }
        }

        computed[index] = true;

        return len_arr[index] = max;
    }
}

