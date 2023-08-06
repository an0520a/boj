#include <iostream>
#include <vector>
#include <array>

std::pair<size_t, size_t> FindMaximumSubarray(const std::vector<int>& vec, std::pair<size_t, size_t> range);

int main()
{
    std::ios_base::sync_with_stdio(false);

    size_t test_case_size;

    std::cin >> test_case_size;

    for (size_t test_case_round = 0; test_case_round < test_case_size; test_case_round++)
    {
        std::vector<int> vec;
        size_t vec_size;

        std::cin >> vec_size;
        vec.resize(vec_size);

        for (size_t i = 0; i < vec_size; i++)
        {
            std::cin >> vec[i];
        }

        auto [front, back] = FindMaximumSubarray(vec, {0, vec_size - 1});
        int sum = 0;

        for (size_t i = front; i <= back; i++)
        {
            sum += vec[i];
        }

        std::cout << sum << std::endl;
    }
}

std::pair<size_t, size_t> FindMaximumSubarray(const std::vector<int>& vec, std::pair<size_t, size_t> range)
{
    constexpr auto get_sum = [](const std::vector<int>& vec, std::pair<size_t, size_t> range)->int
    {
        int sum = 0;

        for (size_t i = range.first; i <=range.second; i++)
        {
            sum += vec[i];
        }

        return sum;
    };
    constexpr auto find_middle_maximum_subarray = 
    [](const std::vector<int>& vec, size_t front, size_t mid, size_t back)->std::pair<size_t, size_t>
    {
        int sum = 0;
        int max_sum = 0;
        size_t mid_left = mid, mid_right = mid + 1;

        for (size_t i = mid; i > front; i--)
        {
            sum += vec[i];
            
            if(sum > max_sum)
            {
                max_sum = sum;
                mid_left = i;
            }
        }

        sum += vec[front];
        if(sum > max_sum)
        {
            max_sum = sum;
            mid_left = front;
        }

        sum = 0;
        max_sum = 0;

        for (size_t i = mid + 1; i <= back; i++)
        {
            sum += vec[i];
            
            if(sum > max_sum)
            {
                max_sum = sum;
                mid_right = i;
            }
        }

        return {mid_left, mid_right};
    };

    const auto &[front, back] = range;
    size_t mid = (front + back) / 2;
    std::pair<size_t, size_t> result_subarray = { front, front };
    int result_sum = vec[front];

    if (front == back)
    {
        return {front, back};
    }

    if (front <= mid)
    {
        std::pair<size_t, size_t> left_subarray = FindMaximumSubarray(vec, {front, mid});
        int left_subarray_sum = get_sum(vec, left_subarray);
        result_sum = get_sum(vec, result_subarray);

        result_subarray = (result_sum > left_subarray_sum)? result_subarray : left_subarray; 
    }
    if (back > mid)
    {
        std::pair<size_t, size_t> right_subarray = FindMaximumSubarray(vec, {mid + 1, back});
        int right_subarray_sum = get_sum(vec, right_subarray);
        result_sum = get_sum(vec, result_subarray);

        result_subarray = (result_sum > right_subarray_sum)? result_subarray : right_subarray;
    }
    if (front <= mid && back > mid)
    {
        std::pair<size_t, size_t> mid_subarray = find_middle_maximum_subarray(vec, front, mid, back);
        int mid_subarray_sum = get_sum(vec, mid_subarray);
        result_sum = get_sum(vec, result_subarray);

        result_subarray = (result_sum > mid_subarray_sum)? result_subarray : mid_subarray;
    }

    return result_subarray;
}