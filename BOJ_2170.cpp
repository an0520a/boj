#include <cstdio>
#include <algorithm>

typedef unsigned int u32;

typedef struct _line
{
    int x;
    int y;
} line;

int main()
{
    u32 N;
    line* arr;
    u32 sum = 0;

    scanf(" %u", &N);

    arr = new line[N];
    for (u32 i = 0; i < N; i++) scanf(" %d %d", &arr[i].x, &arr[i].y);

    std::sort(arr, arr + N, [](const line& l1, const line& l2)->bool{ return l1.x < l2.x; });

    int start = arr[0].x;
    int end = arr[0].y;

    for (u32 i = 1; i < N; i++)
    {
        if(arr[i].x < end) end = (arr[i].y > end)? arr[i].y : end;
        else               sum += end - start, start = arr[i].x, end = arr[i].y;
    }
    sum += end - start;

    printf("%u\n", sum);

    delete[] arr;
}