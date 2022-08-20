#include <iostream>

typedef unsigned int u32;
typedef struct _matrix
{
    u32 row;
    u32 col;
} matrix;

using namespace std;

pair<u32, matrix> getMin(matrix* arr, u32 start, u32 end);

int main()
{
    u32 N;
    matrix *arr;

    scanf(" %u", &N);

    arr = (matrix *)malloc(N * sizeof(matrix));

    for (u32 i = 0; i < N; i++) { scanf(" %u %u", &arr[i].row, &arr[i].col); }

    printf("%u\n", getMin(arr, 0, N - 1).first);

    free(arr);
}

pair<u32, matrix> getMin(matrix* arr, u32 start, u32 end)
{
    static u32 count_memo[500][500] = { 0 };
    static matrix matrix_memo[500][500] = { 0 };    
    if(start == end)
    {
        return {0, arr[start]};
    }
    else if(count_memo[start][end])
    {
        return {count_memo[start][end], matrix_memo[start][end]};
    }
    else
    {
        u32 min = 0xFFFFFFFF;
        matrix min_m;

        for (u32 i = start; i < end; i++)
        {
            pair<u32, matrix> tmp1 = getMin(arr, start, i);
            pair<u32, matrix> tmp2 = getMin(arr, i + 1, end);

            if(tmp1.first + tmp2.first + tmp1.second.row * tmp1.second.col * tmp2.second.col < min)
            {
                min = tmp1.first + tmp2.first + tmp1.second.row * tmp1.second.col * tmp2.second.col;
                min_m = {tmp1.second.row, tmp2.second.col};
            }
        }

        count_memo[start][end] = min;
        matrix_memo[start][end] = min_m;

        return {min, min_m};
    }
}