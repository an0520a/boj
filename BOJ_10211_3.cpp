#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);
    size_t test_case_size;

    std::cin >> test_case_size;

    for (size_t tc = 0; tc < test_case_size; tc++)
    {
        int* arr = nullptr;
        size_t arr_size;
        
        int max = INT32_MIN;

        std::cin >> arr_size;

        arr = new int[arr_size + 1];
        
        arr[0] = 0;
        for (size_t i = 1; i <= arr_size; i++)
        {
            std::cin >> arr[i];
            arr[i] += arr[i - 1];
        }

        for (size_t i = 0; i < arr_size; i++)
        {
            for (size_t j = i + 1; j <= arr_size; j++)
            {
                int sum = arr[j] - arr[i];  

                max = std::max(sum, max);
            }
        }

        std::cout << max << std::endl;
    }
}