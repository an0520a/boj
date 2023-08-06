#include <iostream>

uint32_t max3(uint32_t _x, uint32_t _y, uint32_t _z)
{
    return std::max(_x, std::max(_y, _z));
}

int main()
{
    size_t N, M;
    uint32_t max_sum = 0;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> N >> M;

    uint32_t (*paper)[M] = 
    reinterpret_cast<uint32_t (*)[M]>(operator new(sizeof(uint32_t) * N * M, std::align_val_t{alignof(uint32_t)}));

    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < M; j++)
        {
            std::cin >> paper[i][j];
        }
    }

    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < M; j++)
        {
            // XXXX
            if (j + 3 < M)
            {
                max_sum = std::max(max_sum, paper[i][j] + paper[i][j + 1] + paper[i][j + 2] + paper[i][j + 3]);
            }
            
            // X
            // X
            // X
            // X
            if (i + 3 < N)
            {
                max_sum = std::max(max_sum, paper[i][j] + paper[i + 1][j] + paper[i + 2][j] + paper[i + 3][j]);
            }

            
            if (i + 1 < N)
            {
                // XX
                // XX
                if (j + 1 < M)
                {
                    max_sum = std::max(max_sum, paper[i][j] + paper[i][j + 1] + paper[i + 1][j] + paper[i + 1][j + 1]);
                }

                // X   XXX XXX   X XX   XX XXX  X 
                // XXX X     X XXX  XX XX   X  XXX
                if (j + 2 < M)
                {
                    max_sum = 
                    std::max(max_sum, max3(paper[i][j], paper[i][j + 1], paper[i][j + 2]) + paper[i + 1][j] + paper[i + 1][j + 1] + paper[i + 1][j + 2]);

                    max_sum = 
                    std::max(max_sum, max3(paper[i + 1][j], paper[i + 1][j + 1], paper[i + 1][j + 2]) + paper[i][j] + paper[i][j + 1] + paper[i][j + 2]);

                    max_sum = std::max(max_sum, paper[i][j] + paper[i][j + 1] + paper[i + 1][j + 1] + paper[i + 1][j + 2]);
                    max_sum = std::max(max_sum, paper[i][j + 1] + paper[i][j + 2] + paper[i + 1][j] + paper[i + 1][j + 1]);
                }
            }

            // X    X   X    X   X   X XX    X
            // X    XX  XX   X  XX  XX X     X
            // XX    X  X   XX  X    X X    XX
            if (i + 2 < N && j + 1 < M)
            {
                
                max_sum = 
                std::max(max_sum, max3(paper[i][j], paper[i + 1][j], paper[i + 2][j]) + paper[i][j + 1] + paper[i + 1][j + 1] + paper[i + 2][j + 1]);

                max_sum = 
                std::max(max_sum, max3(paper[i][j + 1], paper[i + 1][j + 1], paper[i + 2][j + 1]) + paper[i][j] + paper[i + 1][j] + paper[i + 2][j]);

                max_sum = std::max(max_sum, paper[i][j] + paper[i + 1][j] + paper[i + 1][j + 1] + paper[i + 2][j + 1]);
                max_sum = std::max(max_sum, paper[i][j + 1] + paper[i + 1][j] + paper[i + 1][j + 1] + paper[i + 2][j]);
            }
        }
    }

    std::cout << max_sum << std::endl;

    operator delete(paper);
}