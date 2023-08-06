#include <iostream>
#include <unordered_map>
#include <string>

bool IsInteger(const std::string& _str)
{
    for (auto ch : _str)
    {
        if (ch < '0' || ch > '9') return false;
    }

    return true;
}

int main()
{   
    size_t N, M;
    std::unordered_map<std::string, size_t> code_by_string_table;
    std::string* str_arr = nullptr;

    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::cin >> N >> M;

    for (size_t i = 1; i <= N; i++)
    {
        std::string input_string;

        std::cin >> input_string;

        code_by_string_table.insert(std::make_pair(str_arr[i], i));
    }

    for (size_t i = 0; i < M; i++)
    {
        std::string input_string;

        std::cin >> input_string;

        if (IsInteger(input_string)) // integer
        {
            std::cout << str_arr[std::stoi(input_string)] << '\n';
        }
        else                                    // string
        {
            std::cout << code_by_string_table.at(input_string) << '\n';
        }
    }

    for (size_t i = 1; i <= N; i++) str_arr[i].~basic_string();
    operator delete(str_arr);
}