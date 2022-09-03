#include <cstdio>
#include <memory.h>
#include <malloc.h>
#include <queue>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct StructPoint
{
    u32 y;
    u32 x;
} Point;

int main()
{
    u32 N, M;
    u32 time_of_melting_chese = 0;
    std::queue<Point> chese_que;
    std::queue<Point> air_que;

    scanf(" %u %u", &N, &M);

    bool (*chese_map)[M + 2] = (bool (*)[M + 2])malloc((N + 2) * (M + 2) * sizeof(bool));
    bool (*visited)[M + 2] = (bool (*)[M + 2])calloc((N + 2) * (M + 2), sizeof(bool));
    memset(chese_map[0], false, (M + 2) * sizeof(bool));
    memset(chese_map[N + 1], false, (M + 2) * sizeof(bool));
    memset(visited[0], true, (M + 2) * sizeof(bool));
    memset(visited[N + 1], true, (M + 2) * sizeof(bool));

    for (size_t i = 1; i <= N; i++)
    {
        chese_map[i][0] = false;
        chese_map[i][M + 1] = false;
        visited[i][0] = true;
        visited[i][M + 1] = true;

        for (size_t j = 1; j <= M; j++)
        {
            scanf(" %hhu", chese_map[i] + j);
        }
    }

    air_que.push({1, 1});
    visited[1][1] = true;

    while(!air_que.empty() || !chese_que.empty())
    {
        while(!air_que.empty())
        {
            Point point = air_que.front();
            air_que.pop();

            const Point next_point_arr[4] = { {point.y - 1, point.x}, {point.y + 1, point.x}, {point.y, point.x - 1}, {point.y, point.x + 1}};

            for (const Point& next_point : next_point_arr)
            {
                if (visited[next_point.y][next_point.x] == false)
                {
                    if (chese_map[next_point.y][next_point.x] == false)
                    {
                        visited[next_point.y][next_point.x] = true;
                        air_que.push(next_point);
                    }
                    else
                    {
                        const Point next_near_point_arr[4] = { {next_point.y - 1, next_point.x}, {next_point.y + 1, next_point.x}, {next_point.y, next_point.x - 1}, {next_point.y, next_point.x + 1}};
                        u32 near_out_air_count = 0;

                        for (const Point& next_near_point : next_near_point_arr)
                        {
                            if (visited[next_near_point.y][next_near_point.x] == true && chese_map[next_near_point.y][next_near_point.x] == false)
                                near_out_air_count++;

                            if (near_out_air_count == 2u) break;
                        }

                        if (near_out_air_count == 2)
                        {
                            visited[next_point.y][next_point.x] = true;
                            chese_que.push(next_point);
                        }
                    }
                }
            }
        }

        while(!chese_que.empty())
        {
            Point point = chese_que.front();
            chese_que.pop();

            chese_map[point.y][point.x] = false;
            air_que.push(point);

            const Point next_point_arr[4] = { {point.y - 1, point.x}, {point.y + 1, point.x}, {point.y, point.x - 1}, {point.y, point.x + 1}};

            for (const Point& next_point : next_point_arr)
            {
                if (visited[next_point.y][next_point.x] == false)
                {
                    if (chese_map[next_point.y][next_point.x] == false)
                    {
                        visited[next_point.y][next_point.x] = true;
                        air_que.push(next_point);
                    }
                }
            }
        }

        time_of_melting_chese++;

        // for (size_t i = 1; i <= N; i++)
        // {
        //     for (size_t j = 1; j <= M; j++)
        //     {
        //         printf(" %hhu", chese_map[i][j]);
        //     }
        //     printf("\n");
        // }
        // printf("\n");
    }

    printf("%u\n", time_of_melting_chese - 1);

    delete[] visited;
    delete[] chese_map;
}