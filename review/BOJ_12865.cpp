#include <cstdio>
#include <algorithm>

typedef unsigned int u32;

typedef struct StuctEntry
{
    u32 W;
    u32 V;
} Entry;

int main()
{
    u32 N, K;
    Entry* entry_arr = nullptr;
    u32** S;
    auto max = [](const u32& x, const u32& y)->u32{ return (x > y)? x : y; };

    scanf(" %u %u", &N, &K);

    S = new u32*[N];
    for (size_t i = 0; i < N; i++) S[i] = new u32[K + 1];

    entry_arr = new Entry[N];
    for (size_t i = 0; i < N; i++) scanf(" %u %u", &entry_arr[i].W, &entry_arr[i].V);

    S[0][0] = 0;
    for (size_t j = 1; j <= K; j++)
    {
        if(entry_arr[0].W <= j)
        {
            S[0][j] = entry_arr[0].V;
        }
        else
        {
            S[0][j] = 0;   
        }
    }

    // for (size_t j = 0; j <= K; j++) printf("%u ", S[0][j]);
    // printf("\n");
    for (size_t i = 1; i < N; i++)
    {
        S[i][0] = 0;

        for (size_t j = 1; j <= K; j++)
        {
            if(entry_arr[i].W <= j)
            {
                S[i][j] = max(S[i - 1][j - entry_arr[i].W] + entry_arr[i].V, S[i - 1][j]);
            }
            else
            {
                S[i][j] = S[i - 1][j];
            }
        }

        // for (size_t j = 0; j <= K; j++) printf("%u ", S[i][j]);
        // printf("\n");
    }

    printf("%u\n", S[N - 1][K]);

    delete[] entry_arr;
    for (size_t i = 0; i < N; i++) delete[] S[i];
    delete[] S;
}