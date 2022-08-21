#include <cstdio>

typedef unsigned int u32;

u32 getCount(u32 n, u32 k, u32 j, u32* arr);

int main()
{
    u32 n, k;
    u32* arr;

    scanf(" %u %u", &n, &k);

    arr = new u32[n];

    for (u32 i = 0; i < n; i++) scanf(" %u", arr + i);

    printf("%u\n", getCount(n, k, 0, arr));
    
    delete[] arr;
}

u32 getCount(u32 n, u32 k, u32 j, u32* arr)
{
    static u32 memo[11] = { 0 };

    if     (k == 0)  return 1;
    else if(memo[k]) return memo[k];
    else
    {
        for(u32 i = j; i < n; i++)
        {
            if(k >= arr[i]) memo[k] = memo[k] + getCount(n, k - arr[i], i, arr);
        }

        return memo[k];
    }
}

