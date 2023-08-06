#include <iostream>
#include <string>

int main()
{
    size_t N;
    size_t M;
    size_t count = 0;
    size_t pre_count = 0;
    std::string S;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> N;
    std::cin >> M;
    std::cin >> S;

    for (const char ch : S)
    {
        if      ((pre_count % 2 == 0 && ch == 'I') || (pre_count % 2 == 1 && ch == 'O'))    pre_count++;
        else if (ch == 'I')                                                                 pre_count = 1;
        else                                                                                pre_count = 0;

        if (pre_count % 2 == 1 && pre_count >= N * 2 + 1)
            count++;
    }

    std::cout << count << '\n';
}