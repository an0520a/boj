#include <iostream>

typedef unsigned int u32;

bool isPalindrome(const u32* arr, size_t start, size_t end);

int main()
{
    size_t N, M;
    u32* arr = nullptr;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cin.tie(NULL);

    std::cin >> N;

    arr = new u32[N];
    for (size_t i = 0; i < N; i++)
    {
        std::cin >> arr[i];
    }

    std::cin >> M;

    for (size_t i = 0; i < M; i++)
    {
        u32 start, end;
        std::cin >> start >> end;
        std::cout << (isPalindrome(arr, start - 1, end - 1)? 1 : 0) << "\n";
    }

    delete[] arr;
}

bool isPalindrome(const u32* arr, size_t start, size_t end)
{
    static bool memo[2000][2000];
    static bool calculated[2000][2000] = {false};

    if          (start == end) return true;
    else if (end - start == 1) return arr[start] == arr[end];

    if (calculated[start][end]) return memo[start][end];
    else
    {
        calculated[start][end] = true;

        if (arr[start] == arr[end])
        {
            return memo[start][end] = isPalindrome(arr, start + 1, end - 1);
        }
        else
        {
            return memo[start][end] = false;
        }
    }
}