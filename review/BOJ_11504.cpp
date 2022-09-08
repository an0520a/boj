#include <iostream>
#include <vector>
#include <memory.h>
 
typedef unsigned int u32;

size_t GetMaxBitonic(const std::vector<u32>& sequence);
size_t GetMaxBitonicLeftComp(const std::vector<u32>& sequence, size_t* left_memo, u32 n_st);
size_t GetMaxBitonicRightComp(const std::vector<u32>& sequence, size_t* right_memo, u32 n_st);

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

    std::cout << GetMaxBitonic(num_sequence) << std::endl;
}

size_t GetMaxBitonic(const std::vector<u32>& sequence)
{
    size_t* left_memo = new size_t[sequence.size()];
    size_t* right_memo = new size_t[sequence.size()];

    memset(left_memo, 0, sequence.size() * sizeof(size_t));
    memset(right_memo, 0, sequence.size() * sizeof(size_t));

    left_memo[0] = 1;
    right_memo[sequence.size() - 1] = 1;

    size_t max = 0;

    for (size_t i = 0; i < sequence.size(); i++)
    {
        size_t tmp = GetMaxBitonicLeftComp(sequence, left_memo, i);
        tmp += GetMaxBitonicRightComp(sequence, right_memo, i);

        max = (max > tmp)? max : tmp;
    }

    return max - 1;
}

size_t GetMaxBitonicLeftComp(const std::vector<u32>& sequence, size_t* left_memo, u32 n_st)
{
    if(left_memo[n_st] == 0)
    {
        size_t max = 0;

        for (size_t i = 0; i < n_st; i++)
        {
            // 어떻게 const &인데, []함수를 호출 가능? 함수에 const 안붙어있음!
            // 이유 : 벡터는 다음 두 연산자 오버로드 함수를 가지고 있음
            // T& operator[](size_type i) { return data_[i]; }
            // const T& operator[](size_type i) const { return data_[i]; }
            
            if(sequence[n_st] > sequence[i])
            {
                size_t tmp = GetMaxBitonicLeftComp(sequence, left_memo, i);
                max = (max > tmp)? max : tmp;
            }
        }

        left_memo[n_st] = max + 1;
    }

    return left_memo[n_st];
}

size_t GetMaxBitonicRightComp(const std::vector<u32>& sequence, size_t* right_memo, u32 n_st)
{
    if(right_memo[n_st] == 0)
    {
        size_t max = 0;

        for (size_t i = n_st + 1; i < sequence.size(); i++)
        {
            if(sequence[n_st] > sequence[i])
            {
                size_t tmp = GetMaxBitonicRightComp(sequence, right_memo, i);
                max = (max > tmp)? max : tmp;
            }
        }

        right_memo[n_st] = max + 1;
    }

    return right_memo[n_st];
}