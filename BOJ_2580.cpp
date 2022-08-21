#include <stdio.h>
#include <vector>
#include <stack>

typedef unsigned int u32;

typedef struct _point
{
    u32 y;
    u32 x;
} point;

typedef struct _entry
{
    point p;
    u32 num;
} entry;


using namespace std;

int main()
{
    u32 sudoku[9][9];
    bool row[9][10] = { 0 };
    bool col[9][10] = { 0 };
    bool sqare[3][3][10] = { 0 };
    vector<entry> vec;
    stack<entry> stk;

    for (u32 i = 0; i < 9; i++)
    {
        for (u32 j = 0; j < 9; j++)
        {
            scanf(" %u", sudoku[i] + j);

            if(sudoku[i][j] != 0)
            {
                row[i][sudoku[i][j]] = true;
                col[j][sudoku[i][j]] = true;
                sqare[i / 3][j / 3][sudoku[i][j]] = true;
            }
            else vec.push_back({i, j, 0});
        }
    }

    bool globalFlag = false;

    do
    {
        if(globalFlag)
        {
            entry next = stk.top();
            stk.pop();

            row[next.p.y][next.num] = col[next.p.x][next.num] = sqare[next.p.y / 3][next.p.x / 3][next.num] = false;

            for (u32 i = next.num + 1; i < 10; i++)
            {
                if(row[next.p.y][i] == false && col[next.p.x][i] == false && sqare[next.p.y / 3][next.p.x / 3][i] == false)
                {
                    row[next.p.y][i] = col[next.p.x][i] = sqare[next.p.y / 3][next.p.x / 3][i] = true;
                    stk.push({next.p, i});
                    globalFlag = false;
                    break;
                } 
            }
        }
        else
        {
            entry next = vec[stk.size()];
            globalFlag = true;

            for(u32 i = 1; i < 10; i++)
            {
                if(row[next.p.y][i] == false && col[next.p.x][i] == false && sqare[next.p.y / 3][next.p.x / 3][i] == false)
                {
                    row[next.p.y][i] = col[next.p.x][i] = sqare[next.p.y / 3][next.p.x / 3][i] = true;
                    stk.push({next.p, i});
                    globalFlag = false;
                    break;
                } 
            }
        }
    } while(stk.size() != vec.size());

    while(!stk.empty())
    {
        sudoku[stk.top().p.y][stk.top().p.x] = stk.top().num;
        stk.pop();
    }

    for (u32 i = 0; i < 9; i++)
    {
        for (u32 j = 0; j < 9; j++)
        {
            printf("%u ", sudoku[i][j]);
        }
        printf("\n");
    }
}