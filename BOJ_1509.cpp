#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>

typedef unsigned short u16;
typedef unsigned int u32;

bool isPalendrome(char* arr, u32 s, u32 e);

int main()
{
    char str[2501];
    u32 len;
    scanf(" %s", str);

    len = strlen(str);

    u16 (*arr)[len] = (u16 (*)[len])calloc((len) * (len), sizeof(u16));

    for (u32 i = 0; i < len; i++)
        arr[0][i] = isPalendrome(str, 0, i);


    for (u32 i = 1; i < len; i++)
    {
        u16 init = arr[i - 1][i - 1];

        for (u32 j = i; j < len; j++)
        {
            arr[i][j] = arr[i - 1][j];

            if(isPalendrome(str, i, j))
            {
                if(arr[i][j] == 0) arr[i][j] = init + 1;
                else               arr[i][j] = ((init + 1) < arr[i][j])? init + 1 : arr[i][j];
            }
        }
    }

    printf("%hu\n", arr[len - 1][len - 1]);

    free(arr);
}

bool isPalendrome(char* arr, u32 s, u32 e)
{
    static bool calculated[2501][2501] = { false };
    static bool memo[2501][2501];

    if(calculated[s][e]) return memo[s][e];
    else if (s == e) return calculated[s][e] = memo[s][e] = true;
    else if (s + 1 == e)
    {
        calculated[s][e] = true;

        if(arr[s] == arr[e]) memo[s][e] = true;
        else                 memo[s][e] = false;

        return memo[s][e];
    }
    else
    {
        calculated[s][e] = true;
        return memo[s][e] = (arr[s] == arr[e] && isPalendrome(arr, s + 1, e - 1));
    }
}