    #include <iostream>

    unsigned long long GetPadovanSequence(size_t N)
    {
        static unsigned long long memo[101] = { 0, 1, 1, 1, 2, 2, 3, 4, 5, 7, 9 };
        if (memo[N]) return memo[N];
        else         return memo[N] = GetPadovanSequence(N - 1) + GetPadovanSequence(N - 5);
    }

    int main()
    {
        size_t test_case_size;

        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);

        std::cin >> test_case_size;

        for (size_t i = 0; i < test_case_size; i++)
        {
            size_t N;

            std::cin >> N;

            std::cout << GetPadovanSequence(N) << '\n';
        }
    }