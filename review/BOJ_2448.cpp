#include <cstdio>
#include <memory.h>

typedef unsigned int u32;

void MakeTriangle(char* arr, u32 ver_size, u32 hor_size);

int main()
{
    u32 N;
    u32 ver_size, hor_size;
    char* arr = nullptr;

    scanf(" %u", &N);

    ver_size = N;
    hor_size = ((ver_size / 3) * 6);

    arr = new char[ver_size * hor_size];
    memset(arr, ' ', ver_size * hor_size);

    for (size_t i = 0; i < ver_size; i++)
    {
        arr[i * hor_size + (hor_size - 1)] = '\n';
    }
    arr[ver_size * hor_size - 1] = '\0';

    MakeTriangle(arr, ver_size, hor_size);

    printf("%s\n", arr);

    delete[] arr;
}

void MakeTriangle(char* arr, u32 ver_size, u32 hor_size)
{
    if(ver_size == 3)
    {
        arr[2] = '*';
        arr[hor_size + 1] = '*', arr[hor_size + 3] = '*';
        memset(arr + 2 * hor_size, '*', 5);
    }
    else
    {
        MakeTriangle(arr + (ver_size / 2), ver_size / 2, hor_size);
        MakeTriangle(arr + (ver_size / 2) * hor_size, ver_size / 2, hor_size);
        MakeTriangle(arr + (ver_size / 2) * hor_size + ver_size, ver_size / 2, hor_size);
    }
}