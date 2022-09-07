#include <iostream>
#include <vector>
#include <memory.h>

typedef unsigned int u32;

size_t GetMaxLenOfIncreaseSequence(const std::vector<u32>& num_sequence);
size_t GetMaxLenOfIncreaseSequence_comp(const std::vector<u32>& num_sequence, size_t* memo, u32 n_th);

int main()
{
    std::ios_base::sync_with_stdio(false);

    size_t N;
    std::vector<u32> num_sequence;

    std::cin >> N;

    for (size_t i = 0; i < N; i++)
    {
        u32 tmp;

        std::cin >> tmp;

        num_sequence.push_back(tmp);
    }

    std::cout << GetMaxLenOfIncreaseSequence(num_sequence) << std::endl;
}

size_t GetMaxLenOfIncreaseSequence(const std::vector<u32>& num_sequence)
{
    size_t* memo = new size_t[num_sequence.size()];
    memset(memo, 0, num_sequence.size() * sizeof(size_t));
    memo[0] = 1;

    size_t max = 0;

    for (size_t i = 0; i < num_sequence.size(); i++)
    {
        size_t tmp = GetMaxLenOfIncreaseSequence_comp(num_sequence, memo, i);
        max = (max > tmp)? max : tmp;
    }
    
    delete[] memo;
    
    return max;
}

size_t GetMaxLenOfIncreaseSequence_comp(const std::vector<u32>& num_sequence, size_t* memo, u32 n_th)
{
    if(memo[n_th] == 0)
    {
        for (size_t i = 0; i < n_th; i++)
        {
            if(num_sequence[i] < num_sequence[n_th])
            {
                size_t tmp = GetMaxLenOfIncreaseSequence_comp(num_sequence, memo, i);
                memo[n_th] = (memo[n_th] > tmp)? memo[n_th] : tmp;
            }
        }
        memo[n_th]++;
    }

    return memo[n_th];
}