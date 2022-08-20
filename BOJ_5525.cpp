#include <stdio.h>
#include <stdlib.h>

typedef unsigned int u32;

int main()
{
    u32 N, M, result = 0;
    char* str;
    scanf(" %u", &N);
    scanf(" %u", &M);

    str = (char *)malloc((M + 1) * sizeof(char));
    char* p = str;

    scanf(" %s", str);

    while (*p)
    {
        if (*p == 'I')
        {
            u32 count;
            u32 len;
            p++;

            for (count = 1;; count++, p++)
            {
                if (*p != ((count & 1)? 'O' : 'I'))
                {
                    count--;
                    break;
                }
            }

            len = (count / 2);
            result += (len >= N)? len - N + 1 : 0;
        }
        else
        {
            p++;
        }
    }

    printf("%u\n", result);

    free(str);
}