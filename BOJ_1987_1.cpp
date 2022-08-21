#include <cstdio>
#include <queue>
#include <malloc.h>
#include <memory.h>

typedef unsigned char u8;
typedef unsigned int u32;

class point
{
public:
    point(const u8& _y = 0, const u8& _x = 0, const u8& _count = 0) : y(_y), x(_x), alphabet(0), count(_count) {}
    inline bool operator[](u8 index) { return (alphabet >> index) & 1; }
    inline void set_true(u8 index) { alphabet = alphabet | (0b1 << index); }
    inline void set_false(u8 index) { alphabet = alphabet & (~(0b1 << index)); } 

    u8 y;
    u8 x;
    u32 alphabet; // 크기가 32bit인 bool 배열로 사용
    u8 count;
};

using namespace std;

u32 BFS(char** map, u32 R, u32 C);

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

    printf("%u\n", BFS(map, R, C));

    for (u32 i = 0; i < R; i++)
    {
        delete[] map[i];
    }
    delete[] map;
}

u32 BFS(char** map, u32 R, u32 C)
{
    queue<point> que;
    point start(0, 0, 1);
    start.set_true(map[0][0] - 'A');
    que.push(start);
    u32 max = 0;

    while(!que.empty())
    {
        point p = que.front();
        que.pop();

        max = (p.count > max)? p.count : max;

        if(p.x != 0 && p[map[p.y][p.x - 1] - 'A'] == false)
        {
            point tmp = p;
            tmp.count++;
            tmp.x--;
            tmp.set_true(map[tmp.y][tmp.x] - 'A');
            que.push(tmp);
        }
        if(p.y != 0 && p[map[p.y - 1][p.x] - 'A'] == false)
        {
            point tmp = p;
            tmp.count++;
            tmp.y--;
            tmp.set_true(map[tmp.y][tmp.x] - 'A');
            que.push(tmp);
        }
        if(p.x != C - 1 && p[map[p.y][p.x + 1] - 'A'] == false)
        {
            point tmp = p;
            tmp.count++;
            tmp.x++;
            tmp.set_true(map[tmp.y][tmp.x] - 'A');
            que.push(tmp);
        }
        if(p.y != R - 1 && p[map[p.y + 1][p.x] - 'A'] == false)
        {
            point tmp = p;
            tmp.count++;
            tmp.y++;
            tmp.set_true(map[tmp.y][tmp.x] - 'A');
            que.push(tmp);
        }
    }

    return max;
}