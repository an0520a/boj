#include <iostream>
#include <queue>

int main()
{
    std::priority_queue<unsigned int> heap;
    size_t N;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> N;

    for (size_t i = 0; i < N; i++)
    {
        unsigned int val;

        std::cin >> val;

        if (val == 0)
        {
            if (heap.empty())   std::cout << 0 << '\n';
            else                std::cout << heap.top() << '\n', heap.pop();
        }
        else
        {
            heap.push(val);
        }
    }
} 