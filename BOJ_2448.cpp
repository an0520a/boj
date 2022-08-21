#include <stdio.h>
#include <malloc.h>
#include <memory.h>

typedef unsigned short u32;

void star(char* arr, u32 row, u32 col, u32 size, u32 nl);

int main()
{
    u32 N;
    u32 row_size;
    u32 col_size;
    scanf(" %hu", &N);

    row_size = N;
    col_size = 6 * (N / 3);

    char *arr = (char *)malloc((row_size * col_size + 1) * sizeof(char));
    memset(arr, ' ', row_size * col_size * sizeof(char));
    for(u32 i = 0; i < row_size; i++)
    {
        arr[col_size * i + col_size - 1] = '\n';
    }
    arr[col_size * row_size] = '\0';

    star(arr, 0, 0, row_size, col_size);

    printf("%s", arr);

    free(arr);
}

void star(char* arr, u32 row, u32 col, u32 size, u32 nl)
{
    if(size == 3)
    {
        arr[row * nl + col + 2] = '*'; // "  *  ";
        arr[(row + 1) * nl + col + 1] = '*', arr[(row + 1) * nl + col + 3] = '*'; // " * * "
        arr[(row + 2) * nl + col] = '*', arr[(row + 2) * nl + col + 1] = '*', arr[(row + 2) * nl + col + 2] = '*', arr[(row + 2) * nl + col + 3] = '*';
        arr[(row + 2) * nl + col + 4] = '*'; // "*****"
    }
    else
    {
        u32 new_size = size / 2;
        star(arr, row, col + new_size, new_size, nl);
        star(arr, row + new_size, col, new_size, nl);
        star(arr, row + new_size, col + new_size * 2, new_size, nl);
    }
}