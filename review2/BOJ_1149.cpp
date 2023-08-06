#include <iostream>

int main()
{
    size_t N;
    size_t *before_input_arr = new size_t[3];
    size_t *tmp_arr = new size_t[3];

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> N;

    std::cin >> before_input_arr[0] >> before_input_arr[1] >> before_input_arr[2];

    for (size_t i = 1; i < N; i++)
    {
        size_t input_arr[3];

        std::cin >> input_arr[0] >> input_arr[1] >> input_arr[2];

        tmp_arr[0] = input_arr[0] + std::min(before_input_arr[1], before_input_arr[2]);
        tmp_arr[1] = input_arr[1] + std::min(before_input_arr[0], before_input_arr[2]);
        tmp_arr[2] = input_arr[2] + std::min(before_input_arr[0], before_input_arr[1]);

        std::swap(before_input_arr, tmp_arr);
    }

    std::cout << std::min(before_input_arr[0], std::min(before_input_arr[1], before_input_arr[2])) << std::endl;
}