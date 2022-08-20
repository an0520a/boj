#include <iostream>
#include <memory.h>
#include <string>

typedef unsigned int u32;

using namespace std;

string quadTree(char* arr, u32 row, u32 col, u32 size, u32 nl);

int main()
{
    u32 N;
    string str;
    char* arr;

    scanf(" %u", &N);

    arr = new char[(N + 1) * N];

    for (unsigned int i = 0; i < N; i++)
    {
        scanf(" %s", arr + i * (N + 1));
    }

    str = quadTree(arr, 0, 0, N, N + 1);
    cout << str << "\n";

    delete[] arr;
}

string quadTree(char* arr, u32 row, u32 col, u32 size, u32 nl)
{
    char val = arr[row * nl + col];
    string tmp;

    if (size == 1)
    {
        tmp.push_back(val);
        return tmp;
    }

    for (u32 i = 1; i < size; i++)
    {
        if(arr[row * nl + col + i] != val)
        {
            u32 resize = size / 2;

            tmp.push_back('(');
            tmp += quadTree(arr, row, col, resize, nl);
            tmp += quadTree(arr, row, col + resize, resize, nl);
            tmp += quadTree(arr, row + resize, col, resize, nl);
            tmp += quadTree(arr, row + resize, col + resize, resize, nl);
            tmp.push_back(')');

            return tmp;
        }
    }

    for (u32 i = 1; i < size; i++)
    {
        if (memcmp(arr + row * nl + col, arr + (row + i) * nl + col, size * sizeof(char)))
        {
            u32 resize = size / 2;

            tmp.push_back('(');
            tmp += quadTree(arr, row, col, resize, nl);
            tmp += quadTree(arr, row, col + resize, resize, nl);
            tmp += quadTree(arr, row + resize, col, resize, nl);
            tmp += quadTree(arr, row + resize, col + resize, resize, nl);
            tmp.push_back(')');

            return tmp;
        }
    }

    tmp.push_back(val);
    return tmp;
}