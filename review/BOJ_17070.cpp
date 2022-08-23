#include <cstdio>

typedef unsigned int u32;

typedef struct StructPoint
{
    u32 y;
    u32 x;
} Point;

enum class Direction
{
    kEast,
    kSouthEast,
    kSouth
};

u32 GetCaseNumOfPipe(bool** map, size_t map_size);
u32 GetCaseNumOfPipe_Calu(bool** map, size_t& map_size, Point pipe_location, Direction dir);

int main()
{
    u32 N;
    bool** map;

    scanf(" %u", &N);

    map = new bool*[N];
    for (size_t i = 0; i < N; i++) map[i] = new bool[N];

    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            scanf(" %hhu", map[i] + j);
        }
    }

    printf("%u\n", GetCaseNumOfPipe(map, N));

    for (size_t i = 0; i < N; i++) delete[] map[i];
    delete[] map;
}

u32 GetCaseNumOfPipe(bool** map, size_t map_size)
{
    u32 return_val = 0;

    return_val = GetCaseNumOfPipe_Calu(map, map_size, {0, 1}, Direction::kEast);

    return return_val;
}

u32 GetCaseNumOfPipe_Calu(bool** map, size_t& map_size, Point pipe_location, Direction dir)
{
    if(pipe_location.y == map_size - 1 && pipe_location.x == map_size - 1)
    {
        return 1;
    }
    else
    {
        u32 return_val = 0;

        if (pipe_location.y + 1 != map_size && map[pipe_location.y + 1][pipe_location.x] != true && (dir == Direction::kSouth || dir == Direction::kSouthEast))
        {
            return_val += GetCaseNumOfPipe_Calu(map, map_size, {pipe_location.y + 1, pipe_location.x}, Direction::kSouth);
        }
        if (pipe_location.y + 1 != map_size && pipe_location.x + 1 != map_size && map[pipe_location.y + 1][pipe_location.x] != true && map[pipe_location.y][pipe_location.x + 1] != true && map[pipe_location.y + 1][pipe_location.x + 1] != true)
        {
            return_val += GetCaseNumOfPipe_Calu(map, map_size, {pipe_location.y + 1, pipe_location.x + 1}, Direction::kSouthEast);
        }
        if (pipe_location.x + 1 != map_size && map[pipe_location.y][pipe_location.x + 1] != true && (dir == Direction::kEast || dir == Direction::kSouthEast))
        {
            return_val += GetCaseNumOfPipe_Calu(map, map_size, {pipe_location.y, pipe_location.x + 1}, Direction::kEast);
        }

        return return_val;
    }
}