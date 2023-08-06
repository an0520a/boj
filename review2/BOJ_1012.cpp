#include <iostream>
#include <queue>
#include <array>

int main()
{
    size_t test_case_size;
    size_t row_size, col_size, number_of_cabage;

    std::ios_base::sync_with_stdio(false);

    std::cin >> test_case_size;

    for (size_t tc = 0; tc < test_case_size; tc++)
    {
        size_t required_worm_num = 0;

        std::cin >> col_size >> row_size >> number_of_cabage;

        bool (*map)[col_size + 2] = reinterpret_cast<bool (*)[col_size + 2]>(operator new((row_size + 2) * (col_size + 2) * sizeof(bool)));

        for (size_t i = 0; i < row_size + 2; i++)
            for (size_t j = 0; j < col_size + 2; j++)
                map[i][j] = false;

        for (size_t i = 0; i < number_of_cabage; i++)
        {
            size_t row_i, col_i;

            std::cin >> col_i >> row_i;

            map[row_i + 1][col_i + 1] = true;
        }

        for (size_t i = 1; i <= row_size; i++)
        {
            for (size_t j = 1; j <= col_size; j++)
            {
                if (map[i][j] == true)
                {
                    std::queue<std::pair<size_t, size_t>> que;

                    map[i][j] = false;
                    que.push({i, j});

                    while (!que.empty())
                    {
                        std::pair<size_t, size_t> p = que.front();
                        que.pop();

                        std::array<std::pair<size_t, size_t>, 4> arr = 
                        {
                            std::pair<size_t, size_t>(p.first - 1, p.second), 
                            std::pair<size_t, size_t>(p.first, p.second - 1),
                            std::pair<size_t, size_t>(p.first + 1, p.second),
                            std::pair<size_t, size_t>(p.first, p.second + 1)
                        };

                        for (size_t i = 0; i < arr.size(); i++)
                        {
                            auto [y, x] = arr[i];

                            if (map[y][x] == true)
                            {
                                map[y][x] = false;
                                que.push(arr[i]);
                            }
                        }
                    }

                    que.pop();
                    required_worm_num++;
                }
            }
        }

        std::cout << required_worm_num << std::endl;
    }
}