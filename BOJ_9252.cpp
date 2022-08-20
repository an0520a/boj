#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>

typedef unsigned short u16;
typedef unsigned int u32;

int main()
{
    char str1[1002];
    char str2[1002];
    str1[0] = '0';
    str2[0] = '0';

    u16 strlen1, strlen2;

    scanf(" %s", str1 + 1);
    scanf(" %s", str2 + 1);

    strlen1 = strlen(str1) - 1;
    strlen2 = strlen(str2) - 1;

    u16 (*memo)[strlen1 + 1] = (u16 (*)[strlen1 + 1])malloc((strlen2 + 1) * (strlen1 + 1) * sizeof(u16));
    memset(memo[0], 0x00, (strlen1 + 1) * sizeof(u16));

    for (u16 i = 1; i <= strlen2; i++)
    {
        memo[i][0] = 0;

        for (u16 j = 1; j <= strlen1; j++)
        {
            if(str2[i] == str1[j])
            {
                memo[i][j] = memo[i - 1][j - 1] + 1;
            }
            else
            {
                memo[i][j] = (memo[i - 1][j] > memo[i][j - 1])? memo[i - 1][j] : memo[i][j - 1];   
            }
        }
    }

    printf("%hu\n", memo[strlen2][strlen1]);

    free(memo);
}