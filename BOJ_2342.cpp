#include <cstdio>
#include <algorithm>
#include <vector>
#include <malloc.h>
#include <memory.h>

typedef unsigned int u32;

using namespace std;
int main()
{
    u32 energy[5][5] = { {0, 2, 2, 2, 2}, { 0, 1, 3, 4, 3 }, { 0, 3, 1, 3, 4 }, { 0, 4, 3, 1, 3 }, { 0, 3, 4, 3, 1 } };
    vector<u32> vec;
    
    u32 tmp = 0;
    do
    {
        vec.push_back(tmp);

        scanf(" %u", &tmp);
    } while (tmp);

    u32 (*memo)[5][5] = (u32 (*)[5][5])calloc((vec.size() + 10) * 5 * 5, sizeof(u32));
    memset(memo, 0x0F, (vec.size() + 10) * 5 * 5 * sizeof(u32));

    memo[0][0][0] = 0;
    memo[1][vec[1]][0] = 2;
    memo[1][0][vec[1]] = 2;

    for (u32 i = 1; i < vec.size() - 1; i++)
    {
        for (u32 j = 0; j < 5; j++)
        {
            if(memo[i][vec[i]][j] != 0x0F0F0F0F)
            {
                memo[i + 1][vec[i + 1]][j] //왼발을 옮기는 경우
                = (memo[i][vec[i]][j] + energy[vec[i]][vec[i + 1]] < memo[i + 1][vec[i + 1]][j])? memo[i][vec[i]][j] + energy[vec[i]][vec[i + 1]] : memo[i + 1][vec[i + 1]][j];
                memo[i + 1][vec[i]][vec[i + 1]] // 오른발을 옮기는 경우
                = (memo[i][vec[i]][j] + energy[j][vec[i + 1]] < memo[i + 1][vec[i]][vec[i + 1]])? memo[i][vec[i]][j] + energy[j][vec[i + 1]] : memo[i + 1][vec[i]][vec[i + 1]];
            }
            if(memo[i][j][vec[i]] != 0x0F0F0F0F)
            {
                memo[i + 1][vec[i + 1]][vec[i]] // 왼발을 옮기는 경우
                = (memo[i][j][vec[i]] + energy[j][vec[i + 1]] < memo[i + 1][vec[i + 1]][vec[i]])? memo[i][j][vec[i]] + energy[j][vec[i + 1]] : memo[i + 1][vec[i + 1]][vec[i]];
                memo[i + 1][j][vec[i + 1]] // 오른발을 옮기는 경우
                = (memo[i][j][vec[i]] + energy[vec[i]][vec[i + 1]] < memo[i + 1][j][vec[i + 1]])? memo[i][j][vec[i]] + energy[vec[i]][vec[i + 1]] : memo[i + 1][j][vec[i + 1]];
            }
        }
    }

    u32 min = 0xFFFFFFFF;
    for (u32 j = 0; j < 5; j++)
    {
        int i = vec.size() - 1;
        min = (memo[i][vec[i]][j] < min)? memo[i][vec[i]][j] : min;
        min = (memo[i][j][vec[i]] < min)? memo[i][j][vec[i]] : min;
    }

    printf("%u\n", min);

    free(memo);
}

