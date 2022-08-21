#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct _point
{
    int x;
    int y;
}point;

void merge_sort(point* start, point* end)
{
    if(start +  1 >= end) return;

    u32 size = end - start;

    point* p1 = start;
    point* p1_end = start + (size + 1) / 2;
    point* p2 = p1_end;
    point* p2_end = end;

    merge_sort(p1, p1_end);
    merge_sort(p2, p2_end);

    point* tmp = (point*)malloc(size * sizeof(point));
    point* tmp_p = tmp;

    auto cmp = [](const point& a, const point& b)->bool{return (a.y != b.y)? (a.y > b.y) : (a.x > b.x); };

    while (true)
    {
        if (cmp(*p1, *p2)) { *tmp_p = *p2, p2++; }
        else               { *tmp_p = *p1, p1++; }

        tmp_p++;

        if      (p1 == p1_end) { memcpy(tmp_p, p2, (p2_end - p2) * sizeof(point)); break; }
        else if (p2 == p2_end) { memcpy(tmp_p, p1, (p1_end - p1) * sizeof(point)); break; }
    }

    memcpy(start, tmp, size * sizeof(point));

    free(tmp);
    
}

int main()
{
    u32 N;
    scanf(" %u", &N);

    point* arr = (point*)malloc(N * sizeof(point));

    for (u32 i = 0; i < N; i++)
    {
        int x, y;
        scanf(" %d %d", &x, &y);

        arr[i] = point{x, y};
    }

    merge_sort(arr, arr + N);

    for (u32 i = 0; i < N; i++)
    {
        printf("%d %d\n", arr[i].x, arr[i].y);
    }
}