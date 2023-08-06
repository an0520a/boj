#include <iostream>
#include <set>

int main()
{
    size_t T;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> T;

    for (size_t tc = 0; tc < T; tc++)
    {
        std::multiset<int> red_black_tree;

        size_t k;
        std::cin >> k;

        for (size_t i = 0; i < k; i++)
        {
            char function;
            std::cin >> function;

            if (function == 'I')
            {
                int val;
                std::cin >> val;

                red_black_tree.insert(val);
            }
            else
            {
                int val;

                std::cin >> val;

                if (!red_black_tree.empty())
                {
                    if (val == -1)
                    {
                        red_black_tree.erase(red_black_tree.begin());
                    }
                    else
                    {
                        red_black_tree.erase(--red_black_tree.end());
                    }
                }
            }
        }

        if (red_black_tree.empty())
        {
            std::cout << "EMPTY" << std::endl;
        }
        else
        {
            std::cout << *(--red_black_tree.end()) << ' ' << *red_black_tree.begin() << std::endl;
        }
    }
}