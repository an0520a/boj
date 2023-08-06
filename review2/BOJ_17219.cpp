#include <iostream>
#include <string>
#include <unordered_map>

int main()
{
    size_t N, M;
    std::unordered_map<std::string, std::string> hash_table;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> N >> M;

    for (size_t i = 0; i < N; i++)
    {
        std::string site, password;

        std::cin >> site >> password;

        hash_table.insert(std::make_pair(std::move(site), std::move(password)));
    }

    for (size_t i = 0; i < M; i++)
    {
        std::string site;
        
        std::cin >> site;

        std::cout << hash_table[site] << '\n';
    }
}