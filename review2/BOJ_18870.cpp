#include <iostream>
#include <algorithm>

int main()
{
    size_t N;
    std::pair<size_t, int> *num_entry_arr = nullptr;

    std::cin >> N;

    num_entry_arr = new std::pair<size_t, int>[N];

    for (size_t i = 0; i < N; i++)
    {
        num_entry_arr[i].first = i;
        std::cin >> num_entry_arr[i].second;
    }

    auto pair_value_less = [](const std::pair<size_t, int>& _a, const std::pair<size_t, int>& _b)->bool
    {
        return _a.second < _b.second;
    };

    std::sort(num_entry_arr, num_entry_arr + N, pair_value_less);

    int pre = num_entry_arr[0].second;
    int ziped_pos = 0;
    for (size_t i = 0; i < N; i++)
    {
        if (num_entry_arr[i].second > pre)
        {
            pre = num_entry_arr[i].second;
            ziped_pos++;
        }

        num_entry_arr[i].second = ziped_pos;
    }

    for (size_t i = 0; i < N; i++)
    {
        while (i < num_entry_arr[i].first)
        {
            std::swap(num_entry_arr[i], num_entry_arr[num_entry_arr[i].first]);
        }
    }

    for (size_t i = 0; i < N; i++)
    {
        std::cout << num_entry_arr[i].second << ' ';
    }

    delete[] num_entry_arr;
}