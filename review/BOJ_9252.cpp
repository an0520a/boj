#include <iostream>
#include <cstring>

int main()
{
    char str1[1024] = { '\0' };
    char str2[1024] = { '\0' };
    
    size_t str1_len = 0;
    size_t str2_len = 0;

    std::ios_base::sync_with_stdio(false);

    std::cin >> (str1 + 1);
    std::cin >> (str2 + 1);

    str1_len = strlen(str1 + 1);
    str2_len = strlen(str2 + 1);

    size_t (*len)[str1_len + 1] = (size_t (*)[str1_len + 1])calloc((str2_len + 1) * (str1_len + 1), sizeof(size_t));

    for (size_t i = 1; i <= str2_len; i++)
    {
        for (size_t j = 1; j <= str1_len; j++)
        {
            if(str2[i] == str1[j]) len[i][j] = len[i - 1][j - 1] + 1;
            else                   len[i][j] = std::max(len[i - 1][j], len[i][j - 1]);
        }
    }

    if(len[str2_len][str1_len] != 0)
    {
        char* LCS = new char[len[str2_len][str1_len] + 1];
        LCS[len[str2_len][str1_len]] = '\0';

        size_t i = str2_len, j = str1_len;
        size_t LCS_i = len[str2_len][str1_len] - 1;

        while(i > 0 && j > 0)
        {
            if(str2[i] == str1[j])
            {
                LCS[LCS_i] = str2[i];
                LCS_i--, i--, j--;
            }
            else
            {
                if(len[i - 1][j] > len[i][j - 1]) i--;
                else                              j--;
            }
        }

        std::cout << len[str2_len][str1_len] << std::endl;
        std::cout << LCS << std::endl;

        delete[] LCS;
    }
    else
    {
        std::cout << 0 << std::endl;
    }

    free(len);
}