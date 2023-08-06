#include <cstdio>

int main()
{
    size_t N, K;
    size_t *coin_arr;
    size_t result = 0;

    scanf(" %zu %zu", &N, &K);

    coin_arr = new size_t[N];

    for (size_t i = 0; i < N; i++)
    {
        scanf(" %zu", coin_arr + i);
    }

    for (ssize_t i = N - 1; i >= 0; i--)
    {
        if (K >= coin_arr[i])
        {
            result += K / coin_arr[i];
            K = K % coin_arr[i];
        }
    }

    printf("%zu\n", result);
}