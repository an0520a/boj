#include <iostream>
#include <string>
#include <unordered_set>

int main()
{
    size_t number_of_operatoin;
    std::unordered_set<unsigned int> set;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> number_of_operatoin;

    for (size_t i = 0; i < number_of_operatoin; i++)
    {
        std::string operation;

        std::cin >> operation;

        if (operation == "all")
        {
            for (size_t i = 1; i <= 20; i++)
            {
                set.insert(static_cast<unsigned int>(i));
            }
        }
        else if (operation == "empty")
        {
            set.clear();
        }
        else
        {
            unsigned int val;

            std::cin >> val;

            if (operation == "add")
            {
                set.insert(val);
            }
            else if (operation == "remove")
            {
                set.erase(val);
            }
            else if (operation == "check")
            {
                std::cout << set.contains(val) << '\n';
            }
            else if (operation == "toggle")
            {
                if (set.contains(val))
                {
                    set.erase(val);
                }
                else
                {
                    set.insert(val);
                }
            }
        }
    }
}