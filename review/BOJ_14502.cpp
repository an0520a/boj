#include <iostream>
#include <queue>
#include <memory.h>

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct StructPoint
{
    u32 y;
    u32 x;
} Point;

int main()
{
    u32 N, M;
    size_t map_size;
    size_t clean_room_size = 0;
    size_t max_clean_room_size = 0;
    std::queue<Point> virus_que;
    std::queue<Point> bfs_que;
    
    scanf(" %u %u", &N, &M);

    map_size = N * M;
    u8 (*map)[M + 2] = (u8 (*)[M + 2])malloc((N + 2) * (M + 2) * sizeof(u8));
    u8 (*tmp_map)[M + 2] = (u8 (*)[M + 2])malloc((N + 2) * (M + 2) * sizeof(u8));

    memset(map[0], 1, (M + 2) * sizeof(u8));
    memset(map[N + 1], 1, (M + 2) * sizeof(u8));

    for (size_t i = 1; i <= N; i++)
    {
        map[i][0] = 1;
        map[i][M + 1] = 1;

        for (size_t j = 1; j <= M; j++)
        {
            scanf(" %hhu", &map[i][j]);

            if(map[i][j] == 2) virus_que.push({(u32)i, (u32)j});
            if(map[i][j] == 0) clean_room_size++;
        }
    }

    for (size_t i = 0; i < map_size; i++)
    {
        Point new_wall_point_arr[3];

        new_wall_point_arr[0] = {(u32)((i / M) + 1), (u32)((i % M) + 1)};
        if(map[new_wall_point_arr[0].y][new_wall_point_arr[0].x] != 0) continue; 

        for (size_t j = i + 1; j < map_size; j++)
        {
            new_wall_point_arr[1] = {(u32)((j / M) + 1), (u32)((j % M) + 1)};
            if(map[new_wall_point_arr[1].y][new_wall_point_arr[1].x] != 0) continue; 

            for (size_t k = j + 1; k < map_size; k++)
            {
                new_wall_point_arr[2] = {(u32)((k / M) + 1), (u32)((k % M) + 1)};
                if(map[new_wall_point_arr[2].y][new_wall_point_arr[2].x] != 0) continue;

                size_t pre_clean_room_size = clean_room_size - 3;

                memcpy(tmp_map, map, (N + 2) * (M + 2) * sizeof(u8));
                for (const Point& new_wall_point : new_wall_point_arr)
                {
                    tmp_map[new_wall_point.y][new_wall_point.x] = 1;
                }
                bfs_que = virus_que;

                while(!bfs_que.empty())
                {
                    Point p = bfs_que.front();
                    bfs_que.pop();

                    Point next_point_arr[4] = { {p.y - 1, p.x}, {p.y, p.x - 1}, {p.y + 1, p.x}, {p.y, p.x + 1}};

                    for (const Point& next_point : next_point_arr)
                    {
                        if(tmp_map[next_point.y][next_point.x] == 0)
                        {
                            tmp_map[next_point.y][next_point.x] = 2;
                            bfs_que.push({next_point});

                            pre_clean_room_size--;
                        }
                    }
                }

                max_clean_room_size = std::max(max_clean_room_size, pre_clean_room_size);
            }
        }
    }

    printf("%u\n", max_clean_room_size);
}