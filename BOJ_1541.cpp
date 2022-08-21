#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef unsigned int u32;

int getMin(char* str);

int main()
{
    char str[60];
    char* p = str;
    u32 sum = 0;

    fgets(str, 55, stdin);

    str[strlen(str) - 1] = '\0';

    printf("%d", getMin(str));
}

int getMin(char* str)
{
    char* p = str;
    bool flag = false;

    u32 num = 0;
    int sum = 0;

    while (*p)
    {
        switch (*p)
        {
            case '+':
                if (flag) sum -= num;
                else      sum += num;
                num = 0;
                break;

            case '-':
                if (flag) sum -= num;
                else      sum += num;

                num = 0;
                flag = true;
                break;

            default :
                if (!(*p == '0' && num == 0))
                {
                    num *= 10;
                    num += *p - '0';
                }
                break;
        }

        p++;
    }

    if (flag) sum -= num;
    else      sum += num;

    num = 0;
    flag = true;

    return sum;
}