#include <cstdio>
#include <malloc.h>

typedef unsigned int u32;

class point
{
public:
    inline point(const u32& _y = 0, const u32& _X = 0);
    inline point getLeftDigPoint();
    inline point getRightDigPoint(const u32& size);
    u32 y;
    u32 x;
};

point::point(const u32& _y, const u32& _x) : y(_y), x(_x) {} 
point point::getLeftDigPoint() { return (x > y)? point(0, x - y) : point(y - x, 0); }
point point::getRightDigPoint(const u32& size) { return (((size - 1) - x) > y)? point(0, x + y) : point(y - ((size - 1) - x), size - 1); }

u32 max_b = 0;
u32 max_w = 0;

void black_bishop(bool chessboard[10][10], bool DigCheck[10][10], u32 size, u32 stage, u32 num);
void white_bishop(bool chessboard[10][10], bool DigCheck[10][10], u32 size, u32 stage, u32 num);

int main()
{
    u32 N;

    scanf(" %u", &N);

    bool chessboard[10][10];
    bool DigCheck[10][10] = { 0 };

    for (u32 i = 0; i < N; i++) for (u32 j = 0; j < N; j++) scanf(" %hhu", &chessboard[i][j]);

    black_bishop(chessboard, DigCheck, N, 0, 0);
    white_bishop(chessboard, DigCheck, N, 1, 0);

    printf("%u\n", max_b + max_w);
}

void black_bishop(bool chessboard[10][10], bool DigCheck[10][10], u32 size, u32 stage, u32 num)
{
    max_b = (num > max_b)? num : max_b;

    if(stage < size)
    {
        for (u32 i = 0; i <= stage; i++)
        {
            point tmp = point(stage - i, i).getLeftDigPoint();

            if(chessboard[stage - i][i] == true && DigCheck[tmp.y][tmp.x] == false)
            {
                DigCheck[tmp.y][tmp.x] = true;
                black_bishop(chessboard, DigCheck, size, stage + 2, num + 1);
                DigCheck[tmp.y][tmp.x] = false;
            }
        }

        black_bishop(chessboard, DigCheck, size, stage + 2, num);
    }
    else if(stage < size * 2 - 1)
    {
        for (u32 i = stage - (size - 1); i < size; i++)
        {
            point tmp = point(stage - i, i).getLeftDigPoint();

            if(chessboard[stage - i][i] == true && DigCheck[tmp.y][tmp.x] == false)
            {
                DigCheck[tmp.y][tmp.x] = true;
                black_bishop(chessboard, DigCheck, size, stage + 2, num + 1);
                DigCheck[tmp.y][tmp.x] = false;
            }
        }

        black_bishop(chessboard, DigCheck, size, stage + 2, num);
    }
}

void white_bishop(bool chessboard[10][10], bool DigCheck[10][10], u32 size, u32 stage, u32 num)
{
    max_w = (num > max_w)? num : max_w;

    if(stage < size)
    {
        for (u32 i = 0; i <= stage; i++)
        {
            point tmp = point(stage - i, i).getLeftDigPoint();

            if(chessboard[stage - i][i] == true && DigCheck[tmp.y][tmp.x] == false)
            {
                DigCheck[tmp.y][tmp.x] = true;
                white_bishop(chessboard, DigCheck, size, stage + 2, num + 1);
                DigCheck[tmp.y][tmp.x] = false;
            }
        }

        white_bishop(chessboard, DigCheck, size, stage + 2, num);
    }
    else if(stage < size * 2 - 1)
    {
        for (u32 i = stage - (size - 1); i < size; i++)
        {
            point tmp = point(stage - i, i).getLeftDigPoint();

            if(chessboard[stage - i][i] == true && DigCheck[tmp.y][tmp.x] == false)
            {
                DigCheck[tmp.y][tmp.x] = true;
                white_bishop(chessboard, DigCheck, size, stage + 2, num + 1);
                DigCheck[tmp.y][tmp.x] = false;
            }
        }

        white_bishop(chessboard, DigCheck, size, stage + 2, num);
    }
}