#include <iostream>

int main()
{
    size_t N;
    int* arr = nullptr;
    int *arr_begin = nullptr, *arr_end = nullptr;
    int optimum_low, optimum_high;
    unsigned int optimum_sum = 0xFFFFFFFF;

    std::ios_base::sync_with_stdio(false);

    std::cin >> N;

    arr = new int[N];
    arr_begin = arr;
    arr_end = arr + N - 1;

    for (size_t i = 0; i < N; i++)
    {
        std::cin >> arr[i];
    }

    while(arr_begin < arr_end)
    {
        unsigned int tmp;

        if((tmp = std::abs(*arr_begin + *arr_end)) < optimum_sum)
        {
            optimum_low = *arr_begin;
            optimum_high = *arr_end;
            optimum_sum = tmp;
        }

        if(*arr_begin + *arr_end < 0) arr_begin++;
        else                          arr_end--;
    }

    delete[] arr;

    std::cout << optimum_low << ' ' << optimum_high << std::endl;
}