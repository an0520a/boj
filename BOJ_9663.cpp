#include <cstdio>
#include <malloc.h>
#include <memory.h>
#include <stack>

typedef unsigned int u32;

typedef struct _entry
{
   u32 y;
   u32 x;
} entry;

using namespace std;

int main()
{
    u32 N;
    u32 count = 0;
    scanf(" %u", &N);

    if (N == 1) { printf("1\n"); return 0; }
    else if (N == 2) { printf("0\n"); return 0; }
    else if (N == 3) { printf("0\n"); return 0; }

    bool (*arr)[N] = (bool (*)[N])calloc(N * N, sizeof(bool));
    bool val_y[15] = { false };

    stack<entry> stk;
    stk.push({0, 0});
    arr[0][0] = true;
    val_y[0] = true;

    bool isNOT = false;

    /*
    for (u32 i = 0; i < N; i++)
    {
        for (u32 j = 0; j < N; j++)
            printf("%u ", arr[i][j]);
        printf("\n");
    }
    printf("---------------------\n");
    */

    while(!stk.empty())
    {
        const entry& p = stk.top();

        if (stk.size() == N)
        {
            isNOT = true;
            count++;
        }
        
        if (isNOT)
        {
            u32 next_y = p.y;
            u32 next_x = p.x;
            stk.pop();

            while (isNOT)
            {
                arr[p.y][p.x] = false;
                val_y[p.y] = false;
                bool row_flag = true;
                bool dig_flag = true;

                next_y++;

                if (next_y == N)
                {
                    break;
                }

                if (val_y[next_y] == true) row_flag = false; // 가로선 판별
                if (row_flag == true) // 대각선 판별
                {
                    u32 min_rv = (next_y < next_x)? next_y : next_x;
                    u32 min_lv = ((next_y < ((N - 1) - next_x))? next_y : (N - 1 - next_x));
                    entry right_dig_p = {next_y - min_rv, next_x - min_rv}; // \ 방향
                    entry left_dig_p  = {next_y - min_lv, next_x + min_lv}; // / 방향

                    for (u32 i = 0; right_dig_p.x + i != N && right_dig_p.y + i != N; i++)
                    {
                        if (arr[right_dig_p.y + i][right_dig_p.x + i] == true)
                        {
                            dig_flag = false;
                            break;
                        }
                    }
                    if(dig_flag) for (u32 i = 0; left_dig_p.x - i != 0xFFFFFFFF && left_dig_p.y + i != N; i++)
                    {
                        if (arr[left_dig_p.y + i][left_dig_p.x - i] == true)
                        {
                            dig_flag = false;
                            break;
                        }
                    }
                }

                if (row_flag && dig_flag)
                {
                    arr[next_y][next_x] = true;
                    val_y[next_y] = true;
                    stk.push({next_y, next_x});
                    isNOT = false;
                    break;
                }
            }
        }
        else
        {
            u32 l;

            for (l = 0; l < N; l++)
            {
                u32 next_x = p.x + 1;
                u32 next_y = l;
                bool row_flag = true;
                bool dig_flag = true;

                if (val_y[next_y] == true) row_flag = false; // 가로선 판별
                if (row_flag == true) // 대각선 판별
                {
                    u32 min_rv = (next_y < next_x)? next_y : next_x;
                    u32 min_lv = ((next_y < ((N - 1) - next_x))? next_y : (N - 1 - next_x));
                    entry right_dig_p = {next_y - min_rv, next_x - min_rv}; // \ 방향
                    entry left_dig_p  = {next_y - min_lv, next_x + min_lv}; // / 방향

                    for (u32 i = 0; right_dig_p.x + i != N && right_dig_p.y + i != N; i++)
                    {
                        if (arr[right_dig_p.y + i][right_dig_p.x + i] == true)
                        {
                            dig_flag = false;
                            break;
                        }
                    }
                    if(dig_flag) for (u32 i = 0; left_dig_p.x - i != 0xFFFFFFFF && left_dig_p.y + i != N; i++)
                    {
                        if (arr[left_dig_p.y + i][left_dig_p.x - i] == true)
                        {
                            dig_flag = false;
                            break;
                        }
                    }
                }

                if (row_flag && dig_flag)
                {
                    arr[next_y][next_x] = true;
                    val_y[next_y] = true;
                    stk.push({next_y, next_x});
                    break;
                }
            }

            if (l == N) isNOT = true;
        }

        /*
        for (u32 i = 0; i < N; i++)
        {
            for (u32 j = 0; j < N; j++)
                printf("%u ", arr[i][j]);
            printf("\n");
        }
        printf("---------------------\n");
        */
    }
    printf("%u\n", count);

    free(arr);
}