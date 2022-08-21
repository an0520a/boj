#include <cstdio>
#include <malloc.h>
#include <vector>
#include <algorithm>

typedef unsigned int u32;
typedef unsigned long long u64;
typedef long long i64;

using namespace std;

void combinationSum(vector<int>& vec, int* arr, u32 size, u32 k, u32 sum);
void AcombinationSum(vector<int>& vec, int* arr, u32 size);

template<typename T>
bool myFind(typename vector<T>::iterator begin, typename vector<T>::iterator end, T value);

template<typename T>
typename vector<T>::iterator myLowerBound(typename vector<T>::iterator begin, typename vector<T>::iterator end, T key);

template<typename T>
typename vector<T>::iterator myUpperBound(typename vector<T>::iterator begin, typename vector<T>::iterator end, T key);

int main()
{
    u32 N;
    int *arr;
    u64 count = 0;
    u32 e1, e2;
    vector<int> S1, S2;
    int S;

    scanf(" %u %d", &N, &S);

    arr  = (int *)malloc(N  * sizeof(int));

    for (u32 i = 0; i < N; i++)
    {
        scanf(" %u", arr + i);
    }

    if(N == 1) { printf("%c\n", (arr[0] == S)? '1' : '0'); return 0; }

    e1 = (N + 1) / 2;
    e2 = N - e1;

    AcombinationSum(S1, arr, e1);
    AcombinationSum(S2, arr + e1, e2);

    for (u32 i = 0; i < S1.size(); i++)
    {
        if(S1[i] == S) count++;
    }

    for (u32 i = 0; i < S2.size(); i++)
    {
        if(S2[i] == S) count++;
    }

    sort(S1.begin(), S1.end());
    sort(S2.begin(), S2.end());

    for (u32 i = 0; i < S1.size(); i++)
    {
        int val = S - S1[i];
        auto lower = myLowerBound(S2.begin(), S2.end(), val);
        auto upper = myUpperBound(S2.begin(), S2.end(), val);
        
        if(*lower == val)
        {
            if(*upper == val)
            {
                count += upper - lower + 1;
            }
            else
            {
                count += upper - lower;
            }
        }
    }

    printf("%llu\n", count);

    free(arr);
}

void combinationSum(vector<int>& vec, int* arr, u32 size, u32 k, u32 sum)
{
    if(k == 1)
    {
        for (u32 i = 0; i < size; i++)
        {
            vec.push_back(sum + arr[i]);
        }
    }
    else
    {
        for (u32 i = 0; i <= size - k; i++)
        {
            combinationSum(vec, arr + (i + 1), size - (i + 1), k - 1, sum + arr[i]);
        }
    }
}

void AcombinationSum(vector<int>& vec, int* arr, u32 size)
{
    for (int i = 1; i <= size; i++)
    {
        combinationSum(vec, arr, size, i, 0);
    }
}


template<typename T>
bool myFind(typename vector<T>::iterator begin, typename vector<T>::iterator end, T value)
{
    auto front = begin;
    auto back = end - 1;
    auto middle = front + (back - front + 1) / 2;

    while(back >= front)
    {
        if (value > *middle)
        {
            front = middle + 1;
        }
        else if (value < *middle)
        {
            back = middle - 1;
        }
        else
        {
            return 1;
        }

        middle = front + (back - front + 1) / 2;
    }

    return 0;
}

template<typename T>
typename vector<T>::iterator myLowerBound(typename vector<T>::iterator begin, typename vector<T>::iterator end, T key)
{
    end--;

    auto front = begin;
    auto back = end;

    while(end > begin)
    {
        auto middle = begin + (end - begin) / 2;

        if (key > *middle) begin = middle + 1;
        else               end   = middle;
    }

    return end;
}

template<typename T>
typename vector<T>::iterator myUpperBound(typename vector<T>::iterator begin, typename vector<T>::iterator end, T key)
{
    end--;

    while(end > begin)
    {
        auto middle = begin + (end - begin) / 2;

        if (key >= *middle) begin = middle + 1;
        else                end   = middle;
    }

    return end;
}