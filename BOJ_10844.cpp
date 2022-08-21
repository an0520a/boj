#include <stdio.h>

typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef __uint128_t u128;

using namespace std;

int main()
{
    u32 N;
    u32 result = 0;
    scanf(" %u", &N);

    u32* arr = new u32[10]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    u32* tmp = new u32[10];

    for (u32 i = 2; i <= N; i++)
    {
        for (u32 j = 0; j < 10; j++) tmp[j] = 0;

        tmp[0] = arr[1];
        tmp[9] = arr[8];

        for (u32 i = 1; i < 9; i++)
        {
            tmp[i] = (arr[i - 1] + arr[i + 1]) % 1000000000U;
        }

        u32* k = tmp;
        tmp = arr;
        arr = k;
    }

    for (u32 i = 1; i < 10; i++) result = (result + arr[i]) % 1000000000U;

    printf("%u\n", result);

    delete[] arr;
    delete[] tmp;
}