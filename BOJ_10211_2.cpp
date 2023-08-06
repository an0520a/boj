#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);

    size_t test_case_size;

    std::cin >> test_case_size;

    for (size_t test_case_round = 0; test_case_round < test_case_size; test_case_round++)
    {
        int* arr = nullptr;
        size_t arr_size;
        int max_sum = INT32_MIN;
        int sum = 0;
        size_t subarray_length = 0;
        std::pair<size_t, size_t> subarray = {0, 0};
        
        std::cin >> arr_size;

        arr = new int[arr_size];

        for (size_t i = 0 ; i < arr_size; i++)
        {
            std::cin >> arr[i];

            if (sum > 0)
            {
                sum += arr[i];
                subarray_length++;
            }
            else
            {
                sum = arr[i];
                subarray_length = 0;
            }

            if (sum > max_sum)
            {
                max_sum = sum;
                subarray.first = i - subarray_length;
                subarray.second = i;
            }
        }

        delete[] arr;
        std::cout << max_sum << std::endl;
    }
}