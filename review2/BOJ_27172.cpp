#include <iostream>
#include <algorithm>

int main()
{
    constexpr size_t kMaxInputSize = 1000000;
    size_t N;

    bool exist_arr[kMaxInputSize + 1] = { false };
    int score_arr[kMaxInputSize + 1] = { 0 };
    uint32_t* int_arr = nullptr;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::cin >> N;

    int_arr = new uint32_t[N];

    for (size_t i = 0; i < N ; i++)
    {
        std::cin >> int_arr[i];
        exist_arr[int_arr[i]] = true;
    }

    for (size_t i = 0; i < N; i++)
    {
        for (uint32_t compare_number = 2 * int_arr[i]; compare_number <= kMaxInputSize; compare_number += int_arr[i])
        {
            if (exist_arr[compare_number] == true) 
            {
                score_arr[int_arr[i]]++, score_arr[compare_number]--;
            }
        }
    }

    for (size_t i = 0; i < N; i++)
    {
        std::cout << score_arr[int_arr[i]] << ' ';
    }
    std::cout << std::endl;

    delete[] int_arr;
    int_arr = nullptr;
}