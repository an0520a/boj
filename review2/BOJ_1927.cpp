#include <iostream>
#include <queue>

int main()
{
    size_t N;
    std::priority_queue<unsigned int, std::vector<unsigned int>, std::greater<unsigned int>> min_heap;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> N;

    for (size_t i = 0; i < N; i++)
    {
        unsigned int val;

        std::cin >> val;

        if (val == 0)
        {
            if (min_heap.empty())
            {
                std::cout << 0 << '\n';
            }
            else
            {
                std::cout << min_heap.top() << '\n';
                min_heap.pop();
            }
        }
        else
        {
            min_heap.push(val);
        }
    }
}