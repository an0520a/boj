#include <cstdio>
#include <malloc.h>
#include <vector>
#include <stack>
#include <algorithm>

typedef unsigned int u32;

using namespace std;

template<typename T>
vector<T> getLIS(T* arr, u32 size);

void getWireDelete(pair<u32, u32>* arr, u32 size);

template <typename T>
T* lowerBound(T* begin, T* end, T val);

template <typename T, typename Compare>
T* lowerBound(T* begin, T* end, T val, Compare c);


int main()
{
    u32 N;
    pair<u32, u32>* pair_arr;

    scanf(" %u", &N);

    pair_arr = new pair<u32, u32>[N];

    for (u32 i = 0; i < N; i++)
    {
        scanf(" %u %u", &pair_arr[i].first, &pair_arr[i].second);
    }

    sort(pair_arr, pair_arr + N);

    getWireDelete(pair_arr, N);

    free(pair_arr);
}

void getWireDelete(pair<u32, u32>* arr, u32 size)
{
    pair<u32, u32>* memo_val = (pair<u32, u32> *)malloc(size * sizeof(pair<u32, u32>));
    u32* memo_idx = (u32 *)malloc(size * sizeof(u32));
    u32 memo_size = 0;

    memo_val[0] = *arr;
    memo_idx[0] = 0;
    memo_size++;

    for (u32 i = 1; i < size; i++)
    {
        if(arr[i].second > memo_val[memo_size - 1].second) memo_val[memo_size] = arr[i], memo_idx[i] = memo_size, memo_size++;
        else
        {
            pair<u32, u32>* tmp = lowerBound(memo_val, memo_val + memo_size, arr[i], [](const pair<u32, u32>& x, const pair<u32, u32>& y)->bool{ return x.second > y.second; });
            *tmp = arr[i], memo_idx[i] = tmp - memo_val;
        }
    }

    printf("%u\n", size - memo_size);

    stack<u32> stk;

    int i;
    int idx = memo_size - 1;
    for (i = size - 1; i >= 0 && idx >= 0; i--)
    {
        if(memo_idx[i] == idx) idx--;
        else                   stk.push(arr[i].first);
    }
    for (; i >= 0; i--)
    {
        stk.push(arr[i].first);
    }

    while(!stk.empty()) printf("%u\n", stk.top()), stk.pop();

    free(memo_idx);
    free(memo_val);
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

        if(val > *mid) begin = mid + 1;
        else           end = mid;
    }

    return end;
}

template <typename T, typename Compare>
T* lowerBound(T* begin, T* end, T val, Compare c)
{
    end--;
    
    while(end > begin)
    {
        T* mid = begin + (end - begin) / 2;

        if(c(val, *mid)) begin = mid + 1;
        else             end = mid;
    }

    return end;
}
