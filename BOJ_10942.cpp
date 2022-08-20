#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

typedef unsigned int u32;

bool isPalendrome(u32* arr, u32 s, u32 e);

int main()
{
    u32 N, M;
    u32* arr;
    u32 **pallendrome;
    bool **calculator;

    scanf(" %u", &N);

    arr = (u32 *)malloc((N + 1) * sizeof(u32));
    for (u32 i = 1; i <= N; i++) scanf(" %u", arr + i);

    scanf(" %u", &M);

    while(M--)
    {
        u32 s, e;
        scanf(" %u %u", &s, &e);

        printf("%c\n", isPalendrome(arr, s, e)? '1' : '0');
    }

    free(arr);
}

bool isPalendrome(u32* arr, u32 s, u32 e)
{
    static bool calculated[2401][2401] = { false };
    static bool memo[2401][2401];

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