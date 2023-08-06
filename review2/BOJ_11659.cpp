#include <iostream>

int main()
{
    size_t N, M;
    size_t *num_arr = nullptr;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> N >> M;

    num_arr = new size_t[N];

    for (size_t i = 0, sum = 0; i < N; i++)
    {
        std::cin >> num_arr[i];

        sum += num_arr[i];
        num_arr[i] = sum;
    }

    for (size_t i = 0; i < M; i++)
    {
        size_t front_index, back_index;

        std::cin >> front_index >> back_index;

        if (front_index == 1)
        {
            std::cout << num_arr[back_index - 1] << '\n';
        }
        else
        {
            std::cout << (num_arr[back_index - 1] - num_arr[front_index - 2]) << '\n';
        }
    }

    delete[] num_arr;
}