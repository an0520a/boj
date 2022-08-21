#include <cstdio>
#include <cmath>

typedef unsigned int u32;
typedef unsigned long long u64;
typedef long long i64;

template <typename T>
T* LowerBound(T* begin, T* end, T& val);

int main()
{
    int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int arr3[] = {1};
    int arr4[] = {1, 2};
    int arr5[] = {1, 2, 3};

    for (int i = 0; i <= 11; i++)
    {
        auto tmp = LowerBound(arr1, arr1 + sizeof(arr1) / sizeof(int), i);

        if(tmp != nullptr) printf(" %d\n", tmp - arr1);
        else               printf("none\n");
    }

    for (int i = 0; i <= 12; i++)
    {
        auto tmp = LowerBound(arr2, arr2 + sizeof(arr2) / sizeof(int), i);

        if(tmp != nullptr) printf(" %d\n", tmp - arr2);
        else               printf("none\n");
    }

    for (int i = 0; i <= 4; i++)
    {
        auto tmp = LowerBound(arr3, arr3 + sizeof(arr3) / sizeof(int), i);

        if(tmp != nullptr) printf(" %d\n", tmp - arr3);
        else               printf("none\n");
    }

    for (int i = 0; i <= 11; i++)
    {
        auto tmp = LowerBound(arr4, arr4 + sizeof(arr4) / sizeof(int), i);

        if(tmp != nullptr) printf(" %d\n", tmp - arr4);
        else               printf("none\n");
    }

    for (int i = 0; i <= 11; i++)
    {
        auto tmp = LowerBound(arr5, arr5 + sizeof(arr5) / sizeof(int), i);

        if(tmp != nullptr) printf(" %d\n", tmp - arr5);
        else               printf("none\n");
    }

}

template <typename T>
T* LowerBound(T* begin, T* end, T& val)
{
    if (begin == end)
    {
        return nullptr;
    }

    T* check = end;
    end--;

    while (begin <= end)
    {
        T* mid = begin + ((end - begin) / 2);

        if (*mid < val)
        {
            begin = mid + 1;
        }
        else
        {
            end = mid - 1;
        }
    }
    
    if (begin != check) return begin;
    else                return nullptr;
}