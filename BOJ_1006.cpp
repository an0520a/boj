#include <cstdio>
#include <memory.h>

typedef unsigned int u32;

constexpr u32 min(const u32& x, const u32 & y) { return (x < y)? x : y; }

int main()
{
    u32 T;
    u32 input[2][10001];
    u32 upper[10001];
    u32 lower[10001];
    u32 mid[10001];

    scanf(" %u", &T);

    while(T--)
    {
        u32 N, W;
        u32 result;

        scanf(" %u %u", &N, &W);

        result = 2 * N;
        upper[0] = lower[0] = mid[0] = input[0][0] = input[1][0] = 0;
        for (u32 i = 1; i <= N; i++) scanf(" %u", &input[0][i]);
        for (u32 i = 1; i <= N; i++) scanf(" %u", &input[1][i]);

        // case 1; 처음에 맨 마지막과 이어진게 없을 떄
        upper[1] = 1, lower[1] = 1, mid[1] = (W >= input[0][1] + input[1][1])? 1 : 2;

        for (u32 i = 2; i <= N; i++)
        {
            upper[i] = min((W >= input[0][i - 1] + input[0][i])? lower[i - 1] + 1 : mid[i - 1] + 1, mid[i - 1] + 1);
            lower[i] = min((W >= input[1][i - 1] + input[1][i])? upper[i - 1] + 1 : mid[i - 1] + 1, mid[i - 1] + 1);
            mid[i]   = min(upper[i] + 1, lower[i] + 1);
            mid[i]   = (W >= input[0][i] + input[1][i])? min(mid[i], mid[i - 1] + 1) : mid[i];
            if(W >= input[0][i - 1] + input[0][i] && W >= input[1][i - 1] + input[1][i]) mid[i] = min(mid[i], mid[i - 2] + 2);
        }
        result = min(mid[N], result);

        if(N != 1)
        {
            upper[1] = 1, lower[1] = 1, mid[1] = 2;

            // case 2; 윗 부분이 맨마지막과 이어져있고, 밑 부분은 맨 마지막과 이어져 있지 않을 떄.
            if(W >= input[0][N] + input[0][1])
            {
                upper[2] = 3;
                lower[2] = (W >= input[1][1] + input[1][2])? 2 : 3;
                mid[2]   = lower[2] + 1, mid[2] = (W >= input[0][2] + input[1][2])? min(mid[2], mid[1] + 1) : mid[2];

                for (u32 i = 3; i <= N; i++)
                {
                    upper[i] = min((W >= input[0][i - 1] + input[0][i])? lower[i - 1] + 1 : mid[i - 1] + 1, mid[i - 1] + 1);
                    lower[i] = min((W >= input[1][i - 1] + input[1][i])? upper[i - 1] + 1 : mid[i - 1] + 1, mid[i - 1] + 1);
                    mid[i]   = min(upper[i] + 1, lower[i] + 1);
                    mid[i]   = (W >= input[0][i] + input[1][i])? min(mid[i], mid[i - 1] + 1) : mid[i];
                    if(W >= input[0][i - 1] + input[0][i] && W >= input[1][i - 1] + input[1][i]) mid[i] = min(mid[i], mid[i - 2] + 2);
                }
                
                result = min(result, lower[N]);
            }

            // case 2; 밑 부분이 맨마지막과 이어져있고, 윗 부분은 맨 마지막과 이어져 있지 않을 떄.
            if(W >= input[1][N] + input[1][1])
            {
                upper[2] = (W >= input[0][1] + input[0][2])? 2 : 3;
                lower[2] = 3;
                mid[2]   = upper[2] + 1, mid[2] = (W >= input[0][2] + input[1][2])? min(mid[2], mid[1] + 1) : mid[2];

                for (u32 i = 3; i <= N; i++)
                {
                    upper[i] = min((W >= input[0][i - 1] + input[0][i])? lower[i - 1] + 1 : mid[i - 1] + 1, mid[i - 1] + 1);
                    lower[i] = min((W >= input[1][i - 1] + input[1][i])? upper[i - 1] + 1 : mid[i - 1] + 1, mid[i - 1] + 1);
                    mid[i]   = min(upper[i] + 1, lower[i] + 1);
                    mid[i]   = (W >= input[0][i] + input[1][i])? min(mid[i], mid[i - 1] + 1) : mid[i];
                    if(W >= input[0][i - 1] + input[0][i] && W >= input[1][i - 1] + input[1][i]) mid[i] = min(mid[i], mid[i - 2] + 2);
                }
                
                result = min(result, upper[N]);
            }

            // case 2; 밑과 윗 부분, 모두 맨마지막과 이어져있을 떄.
            if(W >= input[0][N] + input[0][1] && W >= input[1][N] + input[1][1])
            {
                upper[2] = 3;
                lower[2] = 3;
                mid[2]   = 4, mid[2] = (W >= input[0][2] + input[1][2])? min(mid[2], mid[1] + 1) : mid[2];

                for (u32 i = 3; i <= N; i++)
                {
                    upper[i] = min((W >= input[0][i - 1] + input[0][i])? lower[i - 1] + 1 : mid[i - 1] + 1, mid[i - 1] + 1);
                    lower[i] = min((W >= input[1][i - 1] + input[1][i])? upper[i - 1] + 1 : mid[i - 1] + 1, mid[i - 1] + 1);
                    mid[i]   = min(upper[i] + 1, lower[i] + 1);
                    mid[i]   = (W >= input[0][i] + input[1][i])? min(mid[i], mid[i - 1] + 1) : mid[i];
                    if(W >= input[0][i - 1] + input[0][i] && W >= input[1][i - 1] + input[1][i]) mid[i] = min(mid[i], mid[i - 2] + 2);
                }

                result = min(result, mid[N - 1]);
            }
        }


        printf("%u\n", result);
    }

}