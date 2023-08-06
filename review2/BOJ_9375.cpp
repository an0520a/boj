#include <iostream>
#include <unordered_map>
#include <string>

int main()
{
    size_t test_case_size;

    scanf(" %zu", &test_case_size);

    for (size_t tc = 0; tc < test_case_size; tc++)
    {
        char clothes_type[24] = { '\0' };
        size_t number_of_clothes;
        size_t result = 0;
        std::unordered_map<std::string, size_t> map_table;

        scanf(" %zu", &number_of_clothes);

        for (size_t i = 0; i < number_of_clothes; i++)
        {
            scanf(" %*s %s", clothes_type);

            std::string clothes_type_string = clothes_type;

            if (map_table.contains(clothes_type_string))
            {
                map_table[clothes_type]++;
            }
            else
            {
                map_table.insert({clothes_type_string, 2});
            }
        }

        if (map_table.empty())
        {
            result = 0;
        }
        else
        {
            result = map_table.cbegin()->second;
            for (auto iter = ++map_table.cbegin(); iter != map_table.cend(); iter++)
            {
                result *= iter->second;
            }

            result--;
        }

        printf("%zu\n", result);
    }

}