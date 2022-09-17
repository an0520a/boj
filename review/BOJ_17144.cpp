#include <iostream>
#include <malloc.h>
#include <memory.h>

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct StructPoint
{
    i8 y;
    i8 x;
} Point;

int main()
{

    i8 R, C;
    size_t T;
    Point air_cleaner[2] = { {0, 0}, {0, 0} }; // [0] : uppper, [1] : lower

    std::ios_base::sync_with_stdio(false);

    {
        i16 tmpR, tmpC;
        std::cin >> tmpR >> tmpC >> T;

        R = tmpR;
        C = tmpC;
    }

    i16 (*map)[C] = (i16 (*)[C])malloc(R * C * sizeof(i16));
    i16 (*next_map)[C] = (i16 (*)[C])malloc(R * C * sizeof(i16));

    bool air_cleaner_find_flag = false;
    for (i8 i = 0; i < R; i++)
    {
        for (i8 j = 0; j < C; j++)
        {
            std::cin >> map[i][j];

            if(map[i][j] == -1 && air_cleaner_find_flag == false)
            {
                air_cleaner_find_flag = true;

                air_cleaner[0] = {(i8)i, (i8)j};
                air_cleaner[1] = {(i8)(i + 1), (i8)j};
            }
        }
    }

    for (size_t time_i = 0; time_i < T; time_i++)
    {
        memset(next_map, 0x00, R * C * sizeof(i16));
        next_map[air_cleaner[0].y][0] = -1;
        next_map[air_cleaner[1].y][0] = -1;

        for (i8 r = 0; r < R; r++)
        {
            for (i8 c = 0; c < C; c++)
            {
                if(map[r][c] != -1)
                {
                    const Point next_point_arr[4] = { {(i8)(r - 1), c}, {r, (i8)(c - 1)}, {(i8)(r + 1), c}, {r, (i8)(c + 1)} };

                    i16 next_dust_amount = map[r][c] / 5;
                    size_t count = 0;

                    for (const Point& next_point : next_point_arr)
                    {
                        if(next_point.y != -1 && next_point.x != -1 && next_point.y != R && next_point.x != C && next_map[next_point.y][next_point.x] != -1)
                        {
                            next_map[next_point.y][next_point.x] += next_dust_amount;

                            count++;
                        }
                    }

                    next_map[r][c] += map[r][c] - next_dust_amount * count;
                }
            }
        }

        // 상부 순환
        for (i8 r = air_cleaner[0].y - 2; r >= 0; r--)
        {
            next_map[r + 1][0] = next_map[r][0];
        }

        for (i8 c = 1; c <= C - 1; c++)
        {
            next_map[0][c - 1] = next_map[0][c];
        }

        for (i8 r = 1; r <= air_cleaner[0].y; r++)
        {
            next_map[r - 1][C - 1] = next_map[r][C - 1];
        }

        for (i8 c = C - 2; c >= 1; c--)
        {
            next_map[air_cleaner[0].y][c + 1] = next_map[air_cleaner[0].y][c];
        }
        next_map[air_cleaner[0].y][1] = 0;


        // 하부 순환
        for (i8 r = air_cleaner[1].y + 2; r <= R - 1; r++)
        {
            next_map[r - 1][0] = next_map[r][0];
        }

        for (i8 c = 1; c <= C - 1; c++)
        {
            next_map[R - 1][c - 1] = next_map[R - 1][c];
        }

        for (i8 r = R - 2; r >= air_cleaner[1].y; r--)
        {
            next_map[r + 1][C - 1] = next_map[r][C - 1];
        }

        for (i8 c = C - 2; c >= 1; c--)
        {
            next_map[air_cleaner[1].y][c + 1] = next_map[air_cleaner[1].y][c];
        }
        next_map[air_cleaner[1].y][1] = 0;

        i16 (*tmp)[C] = map;
        map = next_map;
        next_map = tmp;
    }

    u32 sum = 0;
    for (i8 r = 0; r < R; r++)
    {
        for (i8 c = 0; c < C; c++)
        {
            sum += map[r][c];
        }
    }
    sum += 2;

    std::cout << sum << std::endl;

    // for (i8 r = 0; r < R; r++)
    // {
    //     for (i8 c = 0; c < C; c++)
    //     {
    //         printf("%02hhi ", map[r][c]);
    //     }

    //     printf("\n");
    // }

    free(next_map);
    free(map);
}