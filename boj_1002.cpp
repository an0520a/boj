#include <cstdio>

typedef unsigned int u32;
typedef unsigned long long u64;
typedef int i32;
typedef long long i64;

int main()
{
    u64 T;

    scanf(" %llu", &T);

    for (size_t i = 0; i < T; i++)
    {
        i64 x1, y1, r1;
        i64 x2, y2, r2;

        scanf(" %lld %lld %lld %lld %lld %lld", &x1, &y1, &r1, &x2, &y2, &r2);

        if (x1 == x2 && y1 == y2 && r1 == r2)
        {
            printf("-1\n");
        }
        else if ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) > (r1 + r2) * (r1 + r2))
        {
            printf("0\n");
        }
        else if ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) == (r1 + r2) * (r1 + r2))
        {
            printf("1\n");
        }
        else
        {
            const i64& max_radius = ((r1 > r2)? r1 : r2);
            const i64& min_radius = ((r1 < r2)? r1 : r2);
            const i64 point_distance = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);


            if ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) < max_radius * max_radius)
            {
                if ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) < (max_radius - min_radius) * (max_radius - min_radius))
                {
                    printf("0\n");
                }
                else if ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) == (max_radius - min_radius) * (max_radius - min_radius))
                {
                    printf("1\n");
                }
                else
                {
                    printf("2\n");
                }
            }
            else
            {
                printf("2\n");
            }
        }
        
        
    }
}