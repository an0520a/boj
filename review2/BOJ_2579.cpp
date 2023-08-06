#include <iostream>
#include <vector>

int main()
{
    size_t numbers_of_stair;
    std::vector<unsigned int> stair_vec;
    std::vector<unsigned int> score_vec;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> numbers_of_stair;

    stair_vec.resize(numbers_of_stair);
    score_vec.resize(numbers_of_stair);

    for (size_t i = 0; i < numbers_of_stair; i++)
    {
        std::cin >> stair_vec[i];
    }

    score_vec[0] = stair_vec[0];
    if (numbers_of_stair >= 2)  score_vec[1] = stair_vec[1] + score_vec[0];
    if (numbers_of_stair >= 3)  score_vec[2] = stair_vec[2] + std::max(score_vec[0], stair_vec[1]);

    for (size_t i = 3; i < numbers_of_stair; i++)
    {
        score_vec[i] = stair_vec[i] + std::max(stair_vec[i - 1] + score_vec[i - 3], score_vec[i - 2]);
    }

    std::cout << score_vec.back() << std::endl;
}