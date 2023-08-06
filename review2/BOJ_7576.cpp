    #include <iostream>
    #include <queue>
    #include <vector>
    #include <tuple>

    int main()
    {
        size_t M, N;
        size_t number_of_unripe = 0;
        size_t time = 0;
        std::queue< std::tuple<size_t, size_t> > point_que;
        std::vector< std::vector<int> > box;

        std::ios_base::sync_with_stdio(false);

        std::cin >> M >> N;

        box.resize(N);
        for (size_t i = 0; i < N; i++)
        {
            box[i].resize(M);

            for (size_t j = 0; j < M; j++)
            {
                std::cin >> box[i][j];

                if (box[i][j] == 1)
                {
                    point_que.push(std::tuple(i, j));
                }
                else if (box[i][j] == 0)
                {
                    number_of_unripe++;
                }
            }
        }
        
        while(point_que.empty() == false && number_of_unripe != 0)
        {
            size_t point_que_size = point_que.size();

            for (size_t i = 0; i < point_que_size; i++)
            {
                std::tuple<size_t, size_t> p = point_que.front();
                point_que.pop();

                auto [y, x] = p;

                std::array<std::tuple<size_t, size_t>, 4> next_p_arr = 
                { std::tuple{y - 1, x}, {y + 1, x}, {y, x - 1}, {y, x + 1} };

                for (const std::tuple<size_t, size_t>& next_p : next_p_arr)
                {
                    auto [y, x] = next_p;

                    if (y < N && x < M && box[y][x] == 0)
                    {
                        box[y][x] = 1;
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