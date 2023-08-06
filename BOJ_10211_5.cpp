#include <iostream>

std::pair<std::pair<size_t, size_t>, int> FindMaximumSubarray(int* begin, int* end);

int main()
{
    std::ios_base::sync_with_stdio(false);

    size_t test_case_size;

    std::cin >> test_case_size;

    for (size_t tr = 0; tr < test_case_size; tr++)
    {
        int* arr = nullptr;
        size_t arr_size;

        std::cin >> arr_size;

        arr = new int[arr_size];
        for (size_t i = 0; i < arr_size; i++)
        {
            std::cin >> arr[i];
        }

        auto [maximum_subarray, maximum_subarray_sum] = FindMaximumSubarray(arr, arr + arr_size);

        std::cout << maximum_subarray_sum << std::endl;

        delete[] arr;
    }
}

std::pair<std::pair<size_t, size_t>, int> FindMaximumSubarray(int* begin, int* end)
{
    size_t arr_size = end - begin;

    int max = *begin;
    int current = *begin;
    std::pair<size_t, size_t> max_subarray = { 0, 0 };
    std::pair<size_t, size_t> current_subarray = { 0, 0 };

    for (size_t i = 1; i < arr_size; i++)
    {
        if (current < 0)
        {
            current = 0;
            current_subarray = { i, i - 1 };
        }

        current += begin[i];
        current_subarray.second++;
        
        if (current > max)
        {
            max = current;
            max_subarray = current_subarray;
        }
    }

    return { max_subarray, max };
}