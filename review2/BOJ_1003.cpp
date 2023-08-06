#include <iostream>

std::pair<unsigned int, unsigned int> dp(unsigned int __num)
{
    static std::pair<unsigned int, unsigned int> memo[41] = { { 1, 0 }, {0, 1} };
    static bool calculated[41] = { true, true };

    if (calculated[__num])
    {
        return memo[__num];
    }
    else
    {
        std::pair<unsigned int, unsigned int> n_2 = dp(__num - 2);
        std::pair<unsigned int, unsigned int> n_1 = dp(__num - 1);
        calculated[__num] = true;

        return memo[__num] = { n_1.first + n_2.first, n_1.second + n_2.second };
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    size_t test_case_size = 0;

    std::cin >> test_case_size;

    for (size_t i = 0; i < test_case_size; i++)
    {
        unsigned int input_value;

        std::cin >> input_value;

        auto [a, b] = dp(input_value);

        std::cout << a << ' ' << b << std::endl;
    }
}