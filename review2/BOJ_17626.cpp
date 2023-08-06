#include <iostream>

size_t GetMinimumSquare(uint64_t num);

int main()
{
    uint64_t N;

    std::cin >> N;

    std::cout << GetMinimumSquare(N) << std::endl;
}

size_t GetMinimumSquare(uint64_t num)
{
    static size_t memo[50001] = { 0, 1 };

    if (memo[num])
    {
        return memo[num];
    }
    else
    {
        memo[num] = UINT64_MAX;

        uint64_t i;

        for (i = 1; i * i < num; i++)
        {
            memo[num] = std::min(memo[num], GetMinimumSquare(i * i) + GetMinimumSquare(num - i * i));
        }

        if (i * i == num)
        {
            memo[num] = 1;
        }

        return memo[num];
    }
} 