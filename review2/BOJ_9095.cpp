#include <iostream>

size_t GetCase(unsigned int number)
{
    static size_t memo[11] = { 0, 1, 2, 4 };

    if (memo[number]) return memo[number];
    else              return memo[number] = GetCase(number - 3) + GetCase(number - 2) + GetCase(number - 1);
}

int main()
{
    size_t T;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> T;

    for (size_t i = 0; i < T; i++)
    {
        unsigned int num;

        std::cin >> num;

        std::cout << GetCase(num) << '\n';
    }
}