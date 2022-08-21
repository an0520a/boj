#include <cstdio>
#include <cstdlib>
#include <memory.h>

typedef unsigned int u32;

typedef struct _triple
{
    u32 a;
    u32 b;
    u32 c;

    void operator+=(const struct _triple& x){ a += x.a, b += x.b, c += x.c; }
} triple;

triple getNumOfPaper(char* paper, u32 row, u32 col, u32 nl, u32 size);

int main()
{
    u32 N;
    scanf(" %d", &N);

    char* paper = (char*)malloc(N * N * sizeof(char));

    for (u32 i = 0; i < N * N; i++)
    {
        scanf(" %hhd", paper + i);
    }

    triple result = getNumOfPaper(paper, 0, 0, N, N);

    printf("%u\n%u\n%u\n", result.a, result.b, result.c);

    free(paper);
}

triple getNumOfPaper(char* paper, u32 row, u32 col, u32 nl, u32 size)
{
    int val = paper[row * nl + col];

    if (size == 1)
    {
        if      (val == -1) return { 1, 0, 0 };
        else if (val ==  1) return { 0, 0, 1 };
        else                return { 0, 1, 0 };
    }

    for(u32 i = 1; i < size; i++) 
    {
        if (paper[row * nl + (col + i)] != val)
        {
            u32 third_size = size / 3;
            triple tmp = { 0, 0, 0 };

            tmp += getNumOfPaper(paper, row, col, nl, third_size);
            tmp += getNumOfPaper(paper, row, col + third_size, nl, third_size);
            tmp += getNumOfPaper(paper, row, col + third_size * 2, nl, third_size);
            tmp += getNumOfPaper(paper, row + third_size, col, nl, third_size);
            tmp += getNumOfPaper(paper, row + third_size, col + third_size, nl, third_size);
            tmp += getNumOfPaper(paper, row + third_size, col + third_size * 2, nl, third_size);
            tmp += getNumOfPaper(paper, row + third_size * 2, col, nl, third_size);
            tmp += getNumOfPaper(paper, row + third_size * 2, col + third_size, nl, third_size);
            tmp += getNumOfPaper(paper, row + third_size * 2, col + third_size * 2, nl, third_size);

            return tmp;
        }
    }


    for (u32 i = 1; i < size; i++)
    {

        if (memcmp(paper + (row + i) * nl + col, paper + row * nl + col, size * sizeof(char)))
        {
            u32 third_size = size / 3;
            triple tmp = { 0, 0, 0 };

            tmp += getNumOfPaper(paper, row, col, nl, third_size);
            tmp += getNumOfPaper(paper, row, col + third_size, nl, third_size);
            tmp += getNumOfPaper(paper, row, col + third_size * 2, nl, third_size);
            tmp += getNumOfPaper(paper, row + third_size, col, nl, third_size);
            tmp += getNumOfPaper(paper, row + third_size, col + third_size, nl, third_size);
            tmp += getNumOfPaper(paper, row + third_size, col + third_size * 2, nl, third_size);
            tmp += getNumOfPaper(paper, row + third_size * 2, col, nl, third_size);
            tmp += getNumOfPaper(paper, row + third_size * 2, col + third_size, nl, third_size);
            tmp += getNumOfPaper(paper, row + third_size * 2, col + third_size * 2, nl, third_size);

            return tmp;
        }
    }

    if      (val == -1) return { 1, 0, 0 };
    else if (val ==  1) return { 0, 0, 1 };
    else                return { 0, 1, 0 };
}