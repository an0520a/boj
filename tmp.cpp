#include <cstdio>
#include <cmath>

typedef unsigned int u32;
typedef unsigned long long u64;
typedef long long i64;
class point
{
public:
    int x;
    int y;

    point operator+(const point& p) const { return {x + p.x, y + p.y}; }
    point operator+=(const point& p) { x += p.x, y += p.y; return *this; }
    point operator-(const point& p) const { return {x - p.x, y - p.y}; }
    point operator-=(const point& p) { x -= p.x, y -= p.y; return *this; }
    u64 size() { return (u64)((i64)x * (i64)x + (i64)y * (i64)y); }
};

using namespace std;

point combinationMin(point *arr, u32 size);
void combinationMin_cmp(point *arr, u32 n, u32 k, point sum, point& min);

int main()
{
    u32 T;
    point arr[20];

    scanf(" %u", &T);

    while(T--)
    {
        u32 N;
        point result = { 0x7FFFFFFF, 0x7FFFFFFF };

        scanf(" %u", &N);

        for (u32 i = 0; i < N; i++)
        {
            int x;
            int y;

            scanf(" %d %d", &x, &y);

            arr[i] = { x, y };
        }

        point min = combinationMin(arr, N);

        printf("%.12lf\n", sqrt(min.size()));
    }

}

point combinationMin(point *arr, u32 size)
{
    point min = { 0x7FFFFFFF, 0x7FFFFFFF };

    combinationMin_cmp(arr, size, size / 2, {0, 0}, min);

    return min;
}

void combinationMin_cmp(point *arr, u32 n, u32 k, point sum, point& min)
{
    if (k == 0)
    {
        for (u32 i = 0; i < n; i++) sum -= arr[i];
        min = (sum.size() < min.size())? sum : min;
    }
    else
    {
        for (u32 i = 0; i <= n - k; i++)
        {
            combinationMin_cmp(arr + (i + 1), n - (i + 1), k - 1, sum + arr[i], min);
            sum -= arr[i];
        }
    }
}