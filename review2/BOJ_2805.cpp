#include <iostream>
#include <algorithm>

int main()
{
    size_t N, M;
    size_t* tree_arr = nullptr;
    size_t min_height = 0;
    size_t max_height = 0;
    size_t height;

    std::cin >> N >> M;

    tree_arr = new size_t[N];

    for (size_t i = 0; i < N; i++)
    {
        std::cin >> tree_arr[i];
        max_height = std::max(max_height, tree_arr[i]);
    }

    while (max_height > min_height)
    {
        size_t mid_height = (min_height + max_height + 1) / 2;
        size_t sum = 0;

        for (size_t i = 0; i < N; i++)
        {
            sum += (tree_arr[i] > mid_height)? tree_arr[i] - mid_height : 0;
        }

        if (sum < M)
        {
            max_height = mid_height - 1;
        }
        else
        {
            min_height = mid_height;
        }
    }

    std::cout << max_height << std::endl;

    delete[] tree_arr;
}   