#include <iostream>
#include <algorithm>

int main()
{
    size_t N;
    size_t count = 0;
    std::pair<size_t, size_t>* meeting_arr = nullptr;
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> N;

    meeting_arr = new std::pair<size_t, size_t>[N];

    for (size_t i = 0; i < N; i++)
    {
        std::cin >> meeting_arr[i].first >> meeting_arr[i].second;
    }

    constexpr static auto compare = [](const std::pair<size_t, size_t>& a, const std::pair<size_t, size_t>& b)->bool
    {
        return (a.second != b.second)? (a.second < b.second) : (a.first < b.first);
    };

    std::sort(meeting_arr, meeting_arr + N, compare);

    for (size_t i = 0, t = 0; i < N; i++)
    {
        if (meeting_arr[i].first >= t)
        {
            t = meeting_arr[i].second;
            count++;
        }
    }

    std::cout << count << std::endl;
}