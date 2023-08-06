#include <iostream>
#include <array>

size_t GetResult(size_t _value)
{
    static std::array<size_t, 1000001> memo = { 0, 0, 1, 1 };

    if (_value == 1)
    {
        return 0;
    }
    else if (memo[_value] != 0)
    {
        return memo[_value];
    }
    else
    {
        size_t min_v = SIZE_MAX;

        if (_value % 3 == 0)    min_v = std::min(min_v, GetResult(_value / 3) + 1);
        if (_value % 2 == 0)    min_v = std::min(min_v, GetResult(_value / 2) + 1);
        min_v = std::min(min_v, GetResult(_value - 1) + 1);

        return memo[_value] = min_v;
    }
}

int main()
{
    size_t N;

    std::cin >> N;

    std::cout << GetResult(N) << std::endl;
}