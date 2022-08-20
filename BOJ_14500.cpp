#include <stdio.h>
#include <stdlib.h>

typedef unsigned int u32;

int main()
{
    u32 N, M, max = 0;

    scanf(" %u %u", &N, &M);

    u32 **arr = (u32**)malloc(N * sizeof(u32*));

    for (u32 i = 0; i < N; i++)
    {
        arr[i] = (u32*)malloc(M * sizeof(u32));

        for (u32 j = 0; j < M; j++)
        {
            scanf(" %u", arr[i] + j);
        }
    }

    for (u32 i = 0; i < N; i++)
    {
        for (u32 j = 0; j < M; j++)
        {
            u32 row_flag = (i < N - 3) + (i < N - 2) + (i < N - 1);
            u32 col_flag = (j < M - 3) + (j < M - 2) + (j < M - 1);
            u32 tmp;

            switch (row_flag)
            {
            case 3:
                tmp = arr[i][j] + arr[i + 1][j] + arr[i + 2][j] + arr[i + 3][j]; // ㅣ 모양
                max = (max > tmp)? max : tmp;
            case 2:
                if (col_flag > 0)
                {
                    tmp = arr[i][j] + arr[i + 1][j] + arr[i + 1][j + 1] + arr[i + 2][j + 1]; // ㄹ 모양
                    max = (max > tmp)? max : tmp;

                    tmp = arr[i][j + 1] + arr[i + 1][j + 1] + arr[i + 1][j] + arr[i + 2][j];
                    max = (max > tmp)? max : tmp;

                    tmp = arr[i][j] + arr[i + 1][j] + arr[i + 2][j] + arr[i + 2][j + 1]; // ㄴ 모양
                    max = (max > tmp)? max : tmp;

                    tmp = arr[i][j] + arr[i + 1][j] + arr[i + 2][j] + arr[i][j + 1];
                    max = (max > tmp)? max : tmp;

                    tmp = arr[i][j + 1] + arr[i + 1][j + 1] + arr[i + 2][j + 1] + arr[i + 2][j];
                    max = (max > tmp)? max : tmp;

                    tmp = arr[i][j + 1] + arr[i + 1][j + 1] + arr[i + 2][j + 1] + arr[i][j];
                    max = (max > tmp)? max : tmp;

                    tmp = arr[i][j] + arr[i + 1][j] + arr[i + 2][j] + arr[i + 1][j + 1]; // ㅏ 모양
                    max = (max > tmp)? max : tmp;

                    tmp = arr[i][j + 1] + arr[i + 1][j + 1] + arr[i + 2][j + 1] + arr[i + 1][j];
                    max = (max > tmp)? max : tmp;
                }
            case 1:
                if (col_flag > 0)
                {
                    tmp = arr[i][j] + arr[i][j + 1] + arr[i + 1][j] + arr[i + 1][j + 1]; // ㅁ 모양
                    max = (max > tmp)? max : tmp;
                }
                if (col_flag > 1)
                {
                    tmp = arr[i][j] + arr[i][j + 1] + arr[i + 1][j + 1] + arr[i + 1][j + 2]; // ㄹ 모양
                    max = (max > tmp)? max : tmp;

                    tmp = arr[i + 1][j] + arr[i + 1][j + 1] + arr[i][j + 1] + arr[i][j + 2];
                    max = (max > tmp)? max : tmp;

                    tmp = arr[i][j] + arr[i + 1][j] + arr[i + 1][j + 1] + arr[i + 1][j + 2]; // ㄴ 모양
                    max = (max > tmp)? max : tmp;

                    tmp = arr[i + 1][j] + arr[i][j] + arr[i][j + 1] + arr[i][j + 2];
                    max = (max > tmp)? max : tmp;

                    tmp = arr[i][j + 2] + arr[i + 1][j] + arr[i + 1][j + 1] + arr[i + 1][j + 2];
                    max = (max > tmp)? max : tmp;

                    tmp = arr[i + 1][j + 2] + arr[i][j] + arr[i][j + 1] + arr[i][j + 2];
                    max = (max > tmp)? max : tmp;

                    tmp = arr[i][j] + arr[i][j + 1] + arr[i][j + 2] + arr[i + 1][j + 1]; // ㅜ 모양
                    max = (max > tmp)? max : tmp;

                    tmp = arr[i + 1][j] + arr[i + 1][j + 1] + arr[i + 1][j + 2] + arr[i][j + 1];
                    max = (max > tmp)? max : tmp;
                }
            default:
                if (col_flag > 2) // 가로의 길이가 4
                {
                    tmp = arr[i][j] + arr[i][j + 1] + arr[i][j + 2] + arr[i][j + 3]; // ㅡ 모양
                    max = (max > tmp)? max : tmp;
                }
            }
        }
    }

    printf("%u\n", max);

    for (u32 i = 0; i < N; i++)
    {
        free(arr[i]);
    }
    free(arr);
}