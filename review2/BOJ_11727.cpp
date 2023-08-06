#include <iostream>

int main()
{
    size_t N;
    size_t memo[1001] = { 1, 1 };

    std::cin >> N;

    for (size_t i = 2; i <= N; i++)
    {
        memo[i] = (2 * memo[i - 2] + memo[i - 1]) % 10007;
    }

    std::cout << memo[N] << std::endl;
}