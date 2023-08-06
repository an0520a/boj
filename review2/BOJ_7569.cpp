#include <iostream>
#include <queue>
#include <vector>
#include <tuple>

int main()
{
    size_t M, N, H;
    size_t number_of_unripe = 0;
    size_t time = 0;
    std::queue< std::tuple<size_t, size_t, size_t> > point_que;
    std::vector< std::vector< std::vector<int> > > box;

    std::ios_base::sync_with_stdio(false);

    std::cin >> M >> N >> H;

    box.resize(H);
    for (size_t i = 0; i < H; i++)
    {
        box[i].resize(N);

        for (size_t j = 0; j < N; j++)
        {
            box[i][j].resize(M);

            for (size_t k = 0; k < M; k++)
            {
                std::cin >> box[i][j][k];

                if (box[i][j][k] == 1)
                {
                    point_que.push(std::tuple(i, j, k));
                }
                else if (box[i][j][k] == 0)
                {
                    number_of_unripe++;
                }
            }
        }
    }
    
    while(point_que.empty() == false && number_of_unripe != 0)
    {
        size_t point_que_size = point_que.size();

        for (size_t i = 0; i < point_que_size; i++)
        {
            std::tuple<size_t, size_t, size_t> p = point_que.front();
            point_que.pop();

            auto [z, y, x] = p;

            std::array<std::tuple<size_t, size_t, size_t>, 6> next_p_arr = 
            { std::tuple(z - 1, y, x), {z + 1, y, x}, {z, y - 1, x}, {z, y + 1, x}, {z, y, x - 1}, {z, y, x + 1} };

            for (const std::tuple<size_t, size_t, size_t>& next_p : next_p_arr)
            {
                auto [z, y, x] = next_p;

                if (z < H && y < N && x < M && box[z][y][x] == 0)
                {
                    box[z][y][x] = 1;
                    number_of_unripe--;
                    point_que.push(next_p);
                }
            }
        }

        time++;
    }

    if (number_of_unripe == 0)
    {
        std::cout << time << std::endl;
    }
    else
    {
        std::cout << -1 << std::endl;
    }
}