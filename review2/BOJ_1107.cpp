#include <iostream>
#include <array>

std::pair<bool, unsigned int> check_available(std::size_t __ch, const std::array<bool, 10>& __available_button_arr)
{
    unsigned int len = 0;

    do
    {
        if (__available_button_arr[__ch % 10] == false)
        {
            return { false, 0 };
        }

        len++;
    } while (__ch /= 10);

    return { true, len };
}

int main()
{
    size_t N;
    size_t numbers_of_disable_buttons;
    size_t required_cycle;
    std::array<bool, 10> available_button_arr;
    available_button_arr.fill(true);

    std::ios_base::sync_with_stdio(false);

    std::cin >> N;
    std::cin >> numbers_of_disable_buttons;

    for (size_t i = 0; i < numbers_of_disable_buttons; i++)
    {
        size_t disable_button;

        std::cin >> disable_button;

        available_button_arr[disable_button] = false;
    }

    required_cycle = (N > 100)? N - 100 : 100 - N;

    for (size_t i = N; i > ((required_cycle > N)? 0 : N - required_cycle); i--)
    {
        const auto [available_flag, len] = check_available(i, available_button_arr);
        if (available_flag == true)
        {
            required_cycle = std::min(required_cycle, N - i + len);
        }
    }

    // check for 0
    const auto [available_flag, len] = check_available(0, available_button_arr);
    if (available_flag == true)
    {
        required_cycle = std::min(required_cycle, N + len);
    }

    for (size_t i = N; i < N + required_cycle; i++)
    {
        const auto [available_flag, len] = check_available(i, available_button_arr);

        if (available_flag == true)
        {
            required_cycle = std::min(required_cycle, i - N + len);
        }
    }

    std::cout << required_cycle << std::endl;
}