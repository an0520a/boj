#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef unsigned int u32;

int main()
{
    u32 str1_len, str2_len, max_i = 0;
    char str1[1005];
    char str2[1005];

    scanf(" %s", str1);
    scanf(" %s", str2);

    str1_len = strlen(str1);
    str2_len = strlen(str2);

    u32 (*max_arr)[str2_len] = (u32 (*)[str2_len])calloc(str1_len * str2_len, sizeof(u32));

    for (u32 i = 0; i < str2_len; i++)
    {
        if (str2[i] == str1[0]) max_arr[0][i] = 1;
    }

    for (u32 i = 1; i < str1_len; i++)
    {
        u32 k = 0;
        u32 b_max_i = 0;
        u32 max = 0;

        for (u32 j = 0; j < str2_len; j++)
        {
            if (str2[j] == str1[i])
            {
                max_arr[i][j] = 1;

                for (; k < j; k++)
                {
                    if (max_arr[i - 1][k] > max)
                    {
                        b_max_i = k;
                        max = max_arr[i - 1][k];
                    }
                    //b_max_i = (max_arr[i - 1][b_max_i] >= max_arr[i - 1][k])? b_max_i : k;
                }

                if (max != 0) max_arr[i][j] = 1 + max_arr[i - 1][b_max_i];
                
                if (max_arr[i][j] < max_arr[i - 1][j])
                {
                    max_arr[i][j] = max_arr[i - 1][j];
                }
            }
            else
            {
                max_arr[i][j] = max_arr[i - 1][j];
            }
        }
    }

    for (u32 i = 1; i < str2_len; i++)
    {
        max_i = (max_arr[str1_len - 1][i] > max_arr[str1_len - 1][max_i])? i : max_i;
    }

    printf("%u\n", max_arr[str1_len - 1][max_i]);

    free(max_arr);
}