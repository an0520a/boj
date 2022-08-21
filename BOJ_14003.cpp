 #include <cstdio>
#include <malloc.h>
#include <vector>

typedef unsigned int u32;

using namespace std;

template<typename T>
vector<T> getLIS(T* arr, u32 size);

template <typename T>
T* lowerBound(T* begin, T* end, T val);

int main()
{
    u32 N;
    int* arr;

    scanf(" %u", &N);

    arr = (int *)malloc(N * sizeof(int));
    for (u32 i = 0; i < N; i++)
    {
        scanf(" %u", arr + i);
    }

    vector<int> LIS = getLIS(arr, N);

    printf("%lu\n", LIS.size());
    for(u32 i = 0; i < LIS.size(); i++) printf("%u ", LIS[i]);
    printf("\n");

    free(arr);
}

template<typename T>
vector<T> getLIS(T* arr, u32 size)
{
    T* memo_val = (T *)malloc(size * sizeof(T));
    u32* memo_idx = (u32 *)malloc(size * sizeof(u32));
    u32 memo_size = 0;

    memo_val[0] = *arr;
    memo_idx[0] = 0;
    memo_size++;

    for (u32 i = 1; i < size; i++)
    {
        if(arr[i] > memo_val[memo_size - 1]) memo_val[memo_size] = arr[i], memo_idx[i] = memo_size, memo_size++;
        else
        {
            T* tmp = lowerBound(memo_val, memo_val + memo_size, arr[i]);
            *tmp = arr[i], memo_idx[i] = tmp - memo_val;
        }
    }

    vector<T> vec;
    vec.resize(memo_size);

    u32 idx = memo_size - 1;
    for (u32 i = size - 1; i > 0; i--)
    {
        if(memo_idx[i] == idx) vec[idx] = arr[i], idx--;
    }

    if(idx == 0) vec[0] = arr[0];

    free(memo_idx);
    free(memo_val);

    return vec;
}

template <typename T>
T* lowerBound(T* begin, T* end, T val)
{
    end--;
    
    while(end > begin)
    {
        T* mid = begin + (end - begin) / 2;

        if(*mid >= val) end = mid;
        else            begin = mid + 1;
    }

    return end;
}