#include <stdio.h>
#include <vector>

typedef unsigned int u32;

typedef struct _point
{
    u32 y;
    u32 x;
} point;

using namespace std;

u32 subABS(const u32& a, const u32& b) { return (a > b)? a - b : b - a; }
u32 getDX(const point& p, const point& q) { return subABS(p.x, q.x) + subABS(p.y, q.y); }

int main()
{
    u32 N, M;
    u32 result = 0xFFFFFFFF;
    scanf(" %u %u", &N, &M);

    vector<point> houseArr;
    vector<point> storeArr;

    for (u32 i = 0; i < N; i++)
    {
        for (u32 j = 0; j < N; j++)
        {
            u32 tmp;
            scanf(" %u", &tmp);

            if      (tmp == 1) houseArr.push_back({i, j});
            else if (tmp == 2) storeArr.push_back({i, j});
        }
    }

    vector<u32> vec;
    vec.push_back(0);
    bool flag = false;

    while(!vec.empty())
    {
        if(vec.back() == storeArr.size())
        {
            vec.pop_back(), flag = true;
            continue;
        }

        if(vec.size() == M)
        {
            u32 preChickenDX = 0;

            for (u32 j = 0; j < houseArr.size(); j++)
            {
                u32 minDX = 0xFF;

                for (u32 k = 0; k < vec.size(); k++)
                {
                    minDX = (getDX(houseArr[j], storeArr[vec[k]]) < minDX)? getDX(houseArr[j], storeArr[vec[k]]) : minDX;
                }

                preChickenDX += minDX;
            }

            result = (preChickenDX < result)? preChickenDX : result;

            vec.back()++;
        }
        else
        {
            if(flag) vec.back()++, flag = false;
            else     vec.push_back(vec.back() + 1);
        }
    }

    printf("%u\n", result);
}