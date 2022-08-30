#include <cstdio>
#include <queue>
#include <malloc.h>
#include <memory.h>

typedef unsigned short u8;
typedef unsigned int u32;
typedef struct StructPointEntry
{
    u32 y;
    u32 x;
    bool can_break_wall_flag;
}PointEntry;

int main()
{
    u32 N, M;
    u32 dist;
    std::queue<PointEntry> que;
    PointEntry answer_point = { 0, 0, false };
    bool flag_find_route = false;

    scanf(" %u %u", &N, &M);

    char (*map)[M + 3] = (char (*)[M + 3])malloc((N + 2) * (M + 3) * sizeof(char));

    memset(map[0], '3', (M + 2) * sizeof(char)), map[0][M + 2] = '\0';
    memset(map[N + 1], '3', (M + 2) * sizeof(char)), map[0][M + 2] = '\0';
    for (size_t i = 1; i <= N; i++)
    {
        scanf(" %s", map[i] + 1);
        map[i][0] = '3';
        map[i][M + 1] = '3';
        map[i][M + 2] = '\0';
    }

    que.push({1, 1, true});
    map[1][1] = '3';
    dist = 1;

    // printf("\n");

    while(!que.empty())
    {
        const u32 round_size = que.size();

        for (size_t i = 0; i < round_size; i++)
        {
            PointEntry p = que.front();

            if(p.y == N && p.x == M)
            {
                printf("%u\n", dist);
                delete[] map;
                return 0;
            }
            char next_map_data = NULL;
            que.pop();

            if(map[p.y + 1][p.x] == '0' || (map[p.y + 1][p.x] == '2' && p.can_break_wall_flag == true)) que.push({p.y + 1, p.x, p.can_break_wall_flag}), map[p.y + 1][p.x] = p.can_break_wall_flag? '3' : '2';
            if(map[p.y][p.x + 1] == '0' || (map[p.y][p.x + 1] == '2' && p.can_break_wall_flag == true)) que.push({p.y, p.x + 1, p.can_break_wall_flag}), map[p.y][p.x + 1] = p.can_break_wall_flag? '3' : '2';
            if(map[p.y - 1][p.x] == '0' || (map[p.y - 1][p.x] == '2' && p.can_break_wall_flag == true)) que.push({p.y - 1, p.x, p.can_break_wall_flag}), map[p.y - 1][p.x] = p.can_break_wall_flag? '3' : '2';
            if(map[p.y][p.x - 1] == '0' || (map[p.y][p.x - 1] == '2' && p.can_break_wall_flag == true)) que.push({p.y, p.x - 1, p.can_break_wall_flag}), map[p.y][p.x - 1] = p.can_break_wall_flag? '3' : '2';
            if((map[p.y + 1][p.x] == '1' && p.can_break_wall_flag == true)) que.push({p.y + 1, p.x, false}), map[p.y + 1][p.x] = '3';
            if((map[p.y][p.x + 1] == '1' && p.can_break_wall_flag == true)) que.push({p.y, p.x + 1, false}), map[p.y][p.x + 1] = '3';
            if((map[p.y - 1][p.x] == '1' && p.can_break_wall_flag == true)) que.push({p.y - 1, p.x, false}), map[p.y - 1][p.x] = '3';
            if((map[p.y][p.x - 1] == '1' && p.can_break_wall_flag == true)) que.push({p.y, p.x - 1, false}), map[p.y][p.x - 1] = '3';
        }

        // for (u32 i = 0; i < N + 2; i++)
        // {
        //     printf("%s\n", map[i]);
        // }
        // printf("\n----------------------------\n\n");

        dist++;
    }

    printf("-1\n");
    delete[] map;
}