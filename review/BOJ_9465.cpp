#include <cstdio>
#include <malloc.h>

typedef unsigned int u32;
typedef unsigned long long u64;

int main()
{
    size_t T;

    scanf(" %llu", &T);

    u32 sticker_arr[2][100000];
    u32 score_arr[2][100000];
    auto max = [](const u32& x, const u32& y)->const u32&{ return (x > y)? x : y; };

    for (size_t i = 0; i < T; i++)
    {
        u32 N;

        scanf(" %u", &N);

        for (size_t i = 0; i < N; i++)
        {
            scanf(" %u", sticker_arr[0] + i);
        }
        for (size_t i = 0; i < N; i++)
        {
            scanf(" %u", sticker_arr[1] + i);
        }

        score_arr[0][0] = sticker_arr[0][0];
        score_arr[1][0] = sticker_arr[1][0];

        if(N != 1)
        {
            score_arr[0][1] = sticker_arr[1][0] + sticker_arr[0][1];
            score_arr[1][1] = sticker_arr[0][0] + sticker_arr[1][1];
        }


        for (size_t i = 2; i < N; i++)
        {
            score_arr[0][i] = max(score_arr[1][i - 1], score_arr[1][i - 2]) + sticker_arr[0][i];
            score_arr[1][i] = max(score_arr[0][i - 1], score_arr[0][i - 2]) + sticker_arr[1][i];
        }


        printf("%u\n", max(score_arr[0][N - 1], score_arr[1][N - 1]));
    }
}