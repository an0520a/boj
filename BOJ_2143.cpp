#include <cstdio>
#include <algorithm>
#include <malloc.h>

typedef unsigned int u32;
typedef unsigned long long u64;

using namespace std;

int main()
{
    int T;
    u32 n, m;
    u64 count = 0;
    u32 sum_n_size;
    u32 sum_m_size;
    u32 k;
    int* arr_n;
    int* sum_n;
    int* arr_m;
    int* sum_m;

    scanf(" %u", &T);

    scanf(" %u", &n);
    arr_n = (int *)malloc(n * sizeof(int));
    sum_n_size = (n * (n - 1) / 2 + n);
    sum_n = (int *)malloc((sum_n_size + 1) * sizeof(int));
    for (u32 i = 0; i < n; i++) scanf(" %d", arr_n + i);

    scanf(" %u", &m);
    arr_m = (int *)malloc(m * sizeof(int));
    sum_m_size = (m * (m - 1) / 2 + m);
    sum_m = (int *)malloc((sum_m_size + 1) * sizeof(int));
    for (u32 i = 0; i < m; i++) scanf(" %d", arr_m + i);

    for (u32 i = 1; i < n; i++) arr_n[i] += arr_n[i - 1];
    for (u32 i = 1; i < m; i++) arr_m[i] += arr_m[i - 1];

    k = 0;
    for (u32 i = 0; i < n; i++)
    {
        sum_n[k] = arr_n[i], k++;

        for (u32 j = i + 1; j < n; j++)
        {
            sum_n[k] = arr_n[j] - arr_n[i], k++;
        }
    }

    k = 0;
    for (u32 i = 0; i < m; i++)
    {
        sum_m[k] = arr_m[i], k++;

        for (u32 j = i + 1; j < m; j++)
        {
            sum_m[k] = arr_m[j] - arr_m[i], k++;
        }
    }

    sort(sum_n, sum_n + sum_n_size);
    sort(sum_m, sum_m + sum_m_size, [](const int& x, const int& y)->bool{ return x > y; });
    sum_n[sum_n_size] = 0x0FFFFFFF;
    sum_m[sum_m_size] = 0x0FFFFFFF;

    int* p = sum_n;
    int* q = sum_m;

    while (p != sum_n + sum_n_size && q != sum_m + sum_m_size)
    {
        int sum = *p + *q;

        if(sum == T)
        {
            u64 p_size = 1;
            u64 q_size = 1;

            while (p < sum_n + sum_n_size && *p == *(p + 1))
            {
                p_size++;
                p++;
            }
            while (q < sum_m + sum_m_size && *q == *(q + 1))
            {
                q_size++;
                q++;
            }

            count += p_size * q_size;
            p++;
            q++;
        }
        else
        {
            if(sum < T) p++;
            else        q++;
        }
    }

    printf("%llu\n", count);

    free(arr_n);
    free(arr_m);
    free(sum_n);
    free(sum_m);  
}