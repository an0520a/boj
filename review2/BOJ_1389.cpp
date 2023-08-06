#include <iostream>
#include <vector>

int main()
{
    size_t N, M;
    size_t p = 0, p_n = __SIZE_MAX__;

    std::ios_base::sync_with_stdio(false);

    std::cin >> N >> M;

    size_t (*dist)[N] = reinterpret_cast<size_t (*)[N]>(operator new(N * N * sizeof(size_t)));
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            if (i == j) dist[i][j] = 0;
            else        dist[i][j] = SIZE_MAX >> 2;
        }
    }

    for (size_t i = 0; i < M; i++)
    {
        size_t u, v;

        std::cin >> u >> v;

        dist[u - 1][v - 1] = 1;
        dist[v - 1][u - 1] = 1;
    }

    for (size_t m = 0; m < N; m++)
    {
        for (size_t u = 0; u < N; u++)
        {
            for (size_t v = 0; v < N; v++)
            {
                dist[u][v] = std::min(dist[u][v], dist[u][m] + dist[m][v]);
            }
        }
    }

    for (size_t i = 0; i < N; i++)
    {
        size_t sum = 0;

        for (size_t j = 0; j < N; j++)
        {
            sum += dist[i][j];
        }

        if (sum < p_n) p = i + 1, p_n = sum;
    }

    std::cout << p << std::endl;

    operator delete(dist);
}