#include <iostream>

int main(int argc, const char* argv[])
{
    char str1[1024] = { '\0', 'A', 'A', 'A', 'A', 'A' };
    char str2[1024] = { '\0' };

    size_t str1_len = 37;
    size_t str2_len = 1;

    size_t (*len)[str1_len + 1] = (size_t (*)[str1_len + 1])calloc((str2_len + 1) * (str1_len + 1), sizeof(size_t));
    len[str1_len][str2_len] = 1;

    if(len[str1_len][str2_len] != 0)
    {
        char* LCS = new char[len[str1_len][str2_len] + 1];
        LCS[len[str1_len][str2_len]] = '\0';

        size_t i = str1_len, j = str2_len;
        size_t LCS_i = len[str1_len][str2_len] - 1;

        while(i > 0 && j > 0)
        {
            // if(str1[i] == str2[j])
            // {
            //     LCS[LCS_i] = str1[i];
            //     LCS_i--, i--, j--;
            // }
            // else
            // {
            //     if(len[i - 1][j] > len[i][j - 1]) i--;
            //     else                              j--;
            // }
        }

        std::cout << len[str1_len][str2_len] << std::endl;
        std::cout << LCS << std::endl;

        delete[] LCS;
    }
    else
    {
        std::cout << 0 << std::endl;
    }

    free(len);
}