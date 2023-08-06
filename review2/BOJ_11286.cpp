#include <iostream>
#include <queue>

template <typename T>
struct AbsGreater
{
    constexpr bool operator()(const T& _value1, const T& _value2) const
    { return (std::abs(_value1) != std::abs(_value2))? (std::abs(_value1) > std::abs(_value2)) : (_value1 > _value2); }
};

int main()
{
    std::priority_queue<int, std::vector<int>, AbsGreater<int>> heap;
    size_t N;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> N;

    for (size_t i = 0; i < N; i++)
    {
        int val;

        std::cin >> val;

        if (val == 0)
        {
            if (heap.empty())
            {
                std::cout << 0 << '\n';
            }
            else
            {
                std::cout << heap.top() << '\n';
                heap.pop();
            }
        }
        else
        {
            heap.push(val);
        }
    }
}