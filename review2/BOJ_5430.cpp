#include <iostream>
#include <regex>

int main()
{
    size_t test_case_size;
    const static std::regex re(R"([0-9]+)", std::regex::optimize);

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> test_case_size;

    for (size_t test_case_count = 0; test_case_count < test_case_size; test_case_count++)
    {
        unsigned char* block = nullptr;
        unsigned char* block_begin = nullptr;
        unsigned char* block_end = nullptr;
        bool reverse_flag = false;
        bool error_flag = false;
        size_t arr_size;
        std::string command;
        std::string arr_by_string;

        std::cin >> command;
        std::cin >> arr_size;
        std::cin >> arr_by_string;

        block = new unsigned char[arr_size];
        block_begin = block, block_end = block;

        for (std::sregex_iterator regex_it(arr_by_string.begin(), arr_by_string.end(), re), regex_it_end; regex_it != regex_it_end; regex_it++)
        {
            if (regex_it->size() != false)
            {
                *block_end = static_cast<unsigned char>(std::stoi(regex_it->str()));
                block_end++;
            }
        }

        for (const char ch : command)
        {
            if (ch == 'R')
            {
                reverse_flag = !reverse_flag;
            }
            else if (ch == 'D')
            {
                if (reverse_flag == false)
                {
                    block_begin++;
                }
                else
                {
                    block_end--;
                }

                if (block_begin > block_end)
                {
                    error_flag = true;
                    break;
                }
            }
        }

        if (error_flag == true)
        {
            std::cout << "error\n";
        }
        else
        {
            std::cout << "[";

            if (reverse_flag == false)
            {
                for (const unsigned char* p = block_begin; p < block_end - 1; p++)
                {
                    std::cout << static_cast<unsigned int>(*p);
                    std::cout << ',';
                }

                if (block_begin < block_end)
                {
                    std::cout << static_cast<unsigned int>(*(block_end - 1));
                }
            }
            else
            {
                for (const unsigned char* p = block_end - 1; p > block_begin; p--)
                {
                    std::cout << static_cast<unsigned int>(*p);
                    std::cout << ',';
                }

                if (block_begin < block_end)
                {
                    std::cout << static_cast<unsigned int>(*block_begin);
                }
            }

            std::cout << "]\n";
        }

        delete[] block;
    }
}