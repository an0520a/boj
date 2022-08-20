#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef unsigned int u32;
typedef unsigned long long u64;

using namespace std;

void merge_sort(int *start, int *end);

int main()
{
    u32 n;
    double avg;
    int sum = 0;
    int mode = 0;
    u32 mode_n = 0;
    u32 mode_n2 = 0;

    scanf(" %d", &n);

    int* arr = (int*)malloc((n + 1) * sizeof(int));
    int *mode_arr = (int *)malloc((n) * sizeof(int));
    int mode_arr_size = 0;

    for (u32 i = 0; i < n; i++) scanf(" %u", arr + i), sum += arr[i];
    arr[n] = 0x80000000;

    merge_sort(arr, arr + n);

    avg = (double)sum / (double)n;

    //for (u32 i = 0; i < n; i++) printf(" %d", arr[i]);
    //printf("\n");

    int tmp = arr[0];
    u32 count = 0;

    for (u32 i = 0; i <= n; i++)
    {
        if (tmp == arr[i])
        {
            count++;
        }
        else
        {
            if      (count > mode_n)
            {
                mode = tmp;
                mode_n = count;
                mode_arr_size = 0;
            }
            else if (count == mode_n)
            {
                mode_arr[mode_arr_size] = tmp;
                mode_arr_size++;
                mode_n2 = count;
            }

            count = 1;
            tmp = arr[i];
        }
    }

    if(avg > 0) printf("%d\n", (int)(avg + 0.5));
    else        printf("%d\n", (int)(avg - 0.5));
    printf("%d\n", arr[n >> 1]);
    if(n == 1) printf("%d\n", arr[0]);
    else if (!mode_arr_size) printf("%d\n", mode);
    else
    {
        mode_arr[mode_arr_size] = mode;
        mode_arr_size++;

        merge_sort(mode_arr, mode_arr + mode_arr_size);
        printf("%d\n", mode_arr[1]);
    }
    printf("%u", arr[n - 1] - arr[0]);
}

void merge_sort(int *start, int *end)
{
    if (start + 1 >= end)
        return;

    u32 size = end - start;

    int *p1 = start;
    int *p1_end = start + (size + 1) / 2;
    int *p2 = p1_end;
    int *p2_end = end;

    merge_sort(p1, p1_end);
    merge_sort(p2, p2_end);

    int *tmp = (int *)malloc(size * sizeof(int));
    int *tmp_p = tmp;

    while (true)
    {
        if (*p1 > *p2) { *tmp_p = *p2, p2++; }
        else           { *tmp_p = *p1, p1++; }

        tmp_p++;

        if      (p1 == p1_end) { memcpy(tmp_p, p2, (p2_end - p2) * sizeof(int)); break; }
        else if (p2 == p2_end) { memcpy(tmp_p, p1, (p1_end - p1) * sizeof(int)); break; }
    }

    memcpy(start, tmp, size * sizeof(int));

    free(tmp);
}