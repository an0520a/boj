#include <iostream>

int main()
{
    size_t tc;
    std::cin >> tc;

    for (size_t tr = 0; tr < tc; tr++)
    {
        int* arr = nullptr;
        std::pair<size_t, size_t>* memo = nullptr;
        int* prefix_sum_arr = nullptr;
        size_t arr_size;

        const auto get_subarr_sum = [prefix_sum_arr](std::pair<size_t, size_t> subarr)->int
        {
            if (subarr.first == 0)  return prefix_sum_arr[subarr.second];
            else                    return prefix_sum_arr[subarr.second] = prefix_sum_arr[subarr.first - 1];
        };

        std::cin >> arr_size;

        arr = new int[arr_size];
        memo = new std::pair<size_t, size_t>[arr_size];
        // prefix_sum_arr = new int[arr_size];

        for (size_t i = 0; i < arr_size; i++)
        {
            std::cin >> arr[i];
        }

        // prefix_sum_arr[0] = arr[0];
        // for (size_t i = 1; i < arr_size; i++)
        // {
        //     prefix_sum_arr[i] = prefix_sum_arr[0] + arr[i];
        // }

        memo[0] = { 0, 0 };
        int max_sum = arr[0];
        int prev_max_j_to_i_sum = INT32_MIN;
        std::pair<size_t, size_t> prev_max_j_to_i = {0, 0};
        int prefix_sum = 0;

        for (size_t i = 1; i < arr_size; i++)
        {
            memo[i] = memo[i - 1];
            int memo_i_sum = max_sum;
            prefix_sum += arr[i];

            if (prev_max_j_to_i_sum >= 0)
            {
                prev_max_j_to_i_sum += arr[i];
                prev_max_j_to_i = { prev_max_j_to_i.first, i };
            }
            else
            {
                prev_max_j_to_i_sum = arr[i];
                prev_max_j_to_i = { i, i };
            }

            if (prefix_sum >= 0)
            {
                max_sum = prefix_sum + max_sum;
                memo[i] = { memo[i - 1].first, i };
                prefix_sum = 0;
            }

            if (prev_max_j_to_i_sum > max_sum)
            {
                memo[i] = prev_max_j_to_i;
                max_sum = prev_max_j_to_i_sum;
                prev_max_j_to_i_sum = INT32_MIN;
            }

            std::cout << "{ " << memo[i].first << ", " << memo[i].second << " }" << std::endl;
        }

        std::cout << max_sum << std::endl;
        std::cout << "{ " << memo[arr_size - 1].first << ", " << memo[arr_size - 1].second << " }" << std::endl;

        delete[] arr;
        delete[] memo;
        // delete[] prefix_sum_arr
    }
}