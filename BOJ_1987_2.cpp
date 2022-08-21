#include <cstdio>
#include <malloc.h>
#include <memory.h>

typedef unsigned char u8;
typedef unsigned int u32;

class point
{
public:
    point(const u32& _y, const u32& _x) : y(_y), x(_x) {}
    u8 y;
    u8 x;
};

using namespace std;

u32 DFS(char** map, u32 R, u32 C);
void DFS_Computed(char** map, u32 R, u32 C, point p, bool* alphabet, u32 count, u32& max);

int main()
{
    u32 R, C;
    char** map;

    scanf(" %u %u", &R, &C);

    map = new char*[R];
    for (u32 i = 0; i < R; i++)
    {
        map[i] = new char[C + 1];
        scanf(" %s", map[i]);
    }

    printf("%u\n", DFS(map, R, C));

    for (u32 i = 0; i < R; i++)
    {
        delete[] map[i];
    }
    delete[] map;
}

u32 DFS(char** map, u32 R, u32 C)
{
    bool alphabet[26] = { 0 };
    u32 max = 0;
    alphabet[map[0][0] - 'A'] = true;

    DFS_Computed(map, R, C, point(0, 0), alphabet, 1, max);

    return max;
}

void DFS_Computed(char** map, u32 R, u32 C, point p, bool* alphabet, u32 count, u32& max)
{
    max = (count > max)? count : max;

    if(p.x != 0 && alphabet[map[p.y][p.x - 1] - 'A'] == false)
    {
        point tmp(p.y, p.x - 1);
        alphabet[map[tmp.y][tmp.x] - 'A'] = true;
        DFS_Computed(map, R, C, tmp, alphabet, count + 1, max);
        alphabet[map[tmp.y][tmp.x] - 'A'] = false;
    }
    if(p.y != 0 && alphabet[map[p.y - 1][p.x] - 'A'] == false)
    {
        point tmp(p.y - 1, p.x);
        alphabet[map[tmp.y][tmp.x] - 'A'] = true;
        DFS_Computed(map, R, C, tmp, alphabet, count + 1, max);
        alphabet[map[tmp.y][tmp.x] - 'A'] = false;
    }
    if(p.x != C - 1 && alphabet[map[p.y][p.x + 1] - 'A'] == false)
    {
        point tmp(p.y, p.x + 1);
        alphabet[map[tmp.y][tmp.x] - 'A'] = true;
        DFS_Computed(map, R, C, tmp, alphabet, count + 1, max);
        alphabet[map[tmp.y][tmp.x] - 'A'] = false;
    }
    if(p.y != R - 1 && alphabet[map[p.y + 1][p.x] - 'A'] == false)
    {
        point tmp(p.y + 1, p.x);
        alphabet[map[tmp.y][tmp.x] - 'A'] = true;
        DFS_Computed(map, R, C, tmp, alphabet, count + 1, max);
        alphabet[map[tmp.y][tmp.x] - 'A'] = false;
    }
}