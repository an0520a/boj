#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>

int main()
{
    size_t N, M;
    std::unordered_set<std::string> name_set;
    std::vector<std::unordered_set<std::string>::const_iterator> iter_vec;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> N >> M;

    for (size_t i = 0; i < N; i++)
    {
        std::string name;

        std::cin >> name;

        name_set.insert(std::move(name));
    }

    std::unordered_set<std::string>::const_iterator end_iter = name_set.end();

    for (size_t i = 0; i < M; i++)
    {
        std::string name;
        std::unordered_set<std::string>::const_iterator iter;

        std::cin >> name;

        iter = name_set.find(name);

        if (iter != end_iter)
        {
            iter_vec.push_back(std::move(iter));
        }
    }


    constexpr static auto compare = [](std::unordered_set<std::string>::const_iterator a, std::unordered_set<std::string>::const_iterator b)->bool
    {
        return *a < *b;
    };
    std::sort(iter_vec.begin(), iter_vec.end(), compare);

    std::cout << iter_vec.size() << '\n';

    for (auto name : iter_vec)
    {
        std::cout << *name << '\n';
    }
}