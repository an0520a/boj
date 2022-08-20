#include <stdio.h>
#include <malloc.h>
#include <memory.h>

typedef unsigned int u32;

typedef struct _point
{
    u32 y;
    u32 x;
} point;

int main()
{
    u32 R, C, T;
    u32 result = 0;
    bool flag = true;
    scanf(" %u %u %u", &R, &C, &T);

    int (*room)[C] = (int (*)[C])malloc(R * C * sizeof(int));
    int (*tmpRoom)[C] = (int (*)[C])malloc(R * C * sizeof(int));

    point airCleanerUpper;
    point airCleanerLower;
    
    for (u32 i = 0; i < R; i++)
    {
        for (u32 j = 0; j < C; j++)
        {
            int tmp;
            scanf(" %d", &tmp);

            if (flag && tmp == -1)
            {
                airCleanerUpper = {i    , j};
                airCleanerLower = {i + 1, j};
                flag = false;
            }
            
            room[i][j] = tmp;
        }
    }

    while(T--)
    {
        memset(tmpRoom, 0, R * C * sizeof(int));

        for (u32 i = 0; i < R; i++) // 미세먼지 확산
        {
            for (u32 j = 0; j < C; j++)
            {
                if(room[i][j] != -1 && room[i][j] != 0)
                {
                    u32 count = 0;
                    int diffusion = room[i][j] / 5;

                    if(i != 0     && room[i - 1][j] != -1) tmpRoom[i - 1][j] += diffusion, count++;
                    if(i != R - 1 && room[i + 1][j] != -1) tmpRoom[i + 1][j] += diffusion, count++;
                    if(j != 0     && room[i][j - 1] != -1) tmpRoom[i][j - 1] += diffusion, count++;
                    if(j != C - 1 && room[i][j + 1] != -1) tmpRoom[i][j + 1] += diffusion, count++;

                    tmpRoom[i][j] += room[i][j] - count * diffusion;
                }
            }
        }

        int windU = 0, windL = 0;
        for (u32 x = airCleanerUpper.x + 1; x < C; x++)
        {
            int tmp = tmpRoom[airCleanerUpper.y][x];
            tmpRoom[airCleanerUpper.y][x] = windU;
            windU = tmp;

            tmp = tmpRoom[airCleanerLower.y][x];
            tmpRoom[airCleanerLower.y][x] = windL;
            windL = tmp;
        }
        for (int y = airCleanerUpper.y - 1; y >= 0; y--)
        {
            int tmp = tmpRoom[y][C - 1];
            tmpRoom[y][C - 1] = windU;
            windU = tmp;
        }
        for (int x = C - 2; x >= 0; x--)
        {
            int tmp = tmpRoom[0][x];
            tmpRoom[0][x] = windU;
            windU = tmp;
        }
        for (u32 y = 1; y < airCleanerUpper.y; y++)
        {
            int tmp = tmpRoom[y][0];
            tmpRoom[y][0] = windU;
            windU = tmp;
        }

        for (u32 y = airCleanerLower.y + 1; y < R; y++)
        {
            int tmp = tmpRoom[y][C - 1];
            tmpRoom[y][C - 1] = windL;
            windL = tmp;
        }
        for (int x = C - 2; x >= 0; x--)
        {
            int tmp = tmpRoom[R - 1][x];
            tmpRoom[R - 1][x] = windL;
            windL = tmp;
        }
        for (int y = R - 2; y > airCleanerLower.y; y--)
        {
            int tmp = tmpRoom[y][0];
            tmpRoom[y][0] = windL;
            windL = tmp;
        }

        tmpRoom[airCleanerUpper.y][airCleanerUpper.x] = -1;
        tmpRoom[airCleanerLower.y][airCleanerLower.x] = -1;

        int (*tmpRoomPointer)[C] = room;
        room = tmpRoom;
        tmpRoom = tmpRoomPointer;
    }

    for (u32 i = 0; i < R; i++)
    {
        for (u32 j = 0; j < C; j++)
        {
            if(room[i][j] != -1) result += room[i][j];
        }
    }

    printf("%u\n", result);

    free(room);
    free(tmpRoom);
}