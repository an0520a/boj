#include <cstdio>
#include <malloc.h>
#include <cstring>

typedef unsigned int u32;

int main()
{
    char str1[1001], str2[1001];

    scanf(" %s", str1);
    scanf(" %s", str2);

    auto max = [](const u32& x, const u32& y)->const u32&{ return (x > y)? x : y; };

    u32 str1_len = strlen(str1);
    u32 str2_len = strlen(str2);
    u32 len[1001][1001] = { { 0 } };

    if (str1[0] == str2[0]) len[0][0] = 1;
    for (size_t j = 1; j < str1_len; j++)
    {
        if (str1[j] == str2[0]) len[0][j] = 1;
        else                    len[0][j] = len[0][j - 1];
    }

    // for (size_t j = 0; j < str1_len; j++)
    // {
    //     printf("%u ", len[0][j]);
    // }
    // printf("\n");

    for (size_t i = 1; i < str2_len; i++)
    {
        if (str1[0] == str2[i]) len[i][0] = 1;
        len[i][0] = max(len[i][0], len[i - 1][0]);

        for (size_t j = 1; j < str1_len; j++)
        {
            if (str1[j] == str2[i]) len[i][j] = len[i - 1][j - 1] + 1;
            else                    len[i][j] = max(len[i - 1][j], len[i][j - 1]);
        }

        // for (size_t j = 0; j < str1_len; j++)
        // {
        //     printf("%u ", len[i][j]);
        // }
        // printf("\n");
    }

    printf("%u\n", len[str2_len - 1][str1_len - 1]);
}