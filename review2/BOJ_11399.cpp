#include <iostream>
#include <algorithm>

int main()
{
    size_t N;
    size_t* time_arr = nullptr;
    size_t sum = 0;

    std::cin >> N;

    time_arr = new size_t[N];

    for (size_t i = 0; i < N; i++)
    {
        std::cin >> time_arr[i];
    }

    std::sort(time_arr, time_arr + N, std::less<size_t>());

    for (size_t i = 0; i < N; i++)
    {
        sum += time_arr[i] * (N - i);
    }

    delete[] time_arr;
    time_arr = nullptr;

    std::cout << sum << std::endl;
}