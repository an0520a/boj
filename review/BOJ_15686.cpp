#include <cstdio>
#include <vector>
#include <memory.h>

typedef unsigned int u32;
typedef struct StructPoint
{
    u32 y;
    u32 x;
} Point;

u32 GetMinChickenDistance(const std::vector<Point>& chicken_location_vec, const std::vector<Point>& house_location_vec, const u32& M);
u32 GetMinChickenDistance_Comp(std::vector<Point>& set_chicken_vec, std::vector<Point>::const_iterator chicken_vec_begin, std::vector<Point>::const_iterator chicken_vec_end, const std::vector<Point>& house_vec, u32 M);

int main()
{
    u32 N, M;
    std::vector<Point> house_location_vec;
    std::vector<Point> chicken_location_vec;

    scanf(" %u %u", &N, &M);

    for (u32 i = 0; i < N; i++)
    {
        for (u32 j = 0; j < N; j++)
        {
            u32 tmp;
            scanf(" %u", &tmp);

            if      (tmp == 1) house_location_vec.push_back({i, j});
            else if (tmp == 2) chicken_location_vec.push_back({i, j});
        }
    }

    u32 result = GetMinChickenDistance(chicken_location_vec, house_location_vec, M);

    printf("%u\n", result);
}

u32 GetMinChickenDistance(const std::vector<Point>& chicken_location_vec, const std::vector<Point>& house_location_vec, const u32& M)
{
    std::vector<Point> set_chicken_vec;
    return GetMinChickenDistance_Comp(set_chicken_vec, chicken_location_vec.begin(), chicken_location_vec.end(), house_location_vec, M);
}

u32 GetMinChickenDistance_Comp(std::vector<Point>& set_chicken_vec, std::vector<Point>::const_iterator chicken_vec_begin, std::vector<Point>::const_iterator chicken_vec_end, const std::vector<Point>& house_vec, u32 M)
{
    static u32 tmp_chicken_diatance_arr[50];
    constexpr auto min = [](const u32& x, const u32& y)->const u32&{ return (x < y)? x : y; };
    constexpr auto dist = [](const Point& p1, const Point& p2)->u32{ return (((p1.y > p2.y)? p1.y - p2.y : p2.y - p1.y) + ((p1.x > p2.x)? p1.x - p2.x : p2.x - p1.x)); };

    if(M == 0)
    {
        u32 sum = 0;
        memset(&tmp_chicken_diatance_arr, 0xFF, house_vec.size() * sizeof(u32));

        for (const Point& chicken_location : set_chicken_vec)
        {
            for (size_t i = 0; i < house_vec.size(); i++)
            {
                tmp_chicken_diatance_arr[i] = min(tmp_chicken_diatance_arr[i], dist(chicken_location, house_vec[i]));
            }
        }


        for (size_t i = 0; i < house_vec.size(); i++)
        {
            sum += tmp_chicken_diatance_arr[i];
        }

        return sum;
    }
    else
    {
        u32 min_dist = 0xFFFFFFFF;
        for (std::vector<Point>::const_iterator iter = chicken_vec_begin; iter != chicken_vec_end - (M - 1); iter++)
        {
            set_chicken_vec.push_back(*iter);
            min_dist = min(min_dist, GetMinChickenDistance_Comp(set_chicken_vec, iter + 1, chicken_vec_end, house_vec, M - 1));
            set_chicken_vec.pop_back();
        }

        return min_dist;
    }

}