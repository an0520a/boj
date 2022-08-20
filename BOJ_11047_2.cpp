#include <iostream>
#include <stack>
#include <algorithm>

typedef unsigned int u32;

using namespace std;

u32 getCoinNum(u32* coin, u32 n, u32 sum);

int main()
{
    u32 N, K;
    u32* coin;
    scanf(" %u %u", &N, &K);

    coin = new u32[N];

    for (u32 i = 0; i < N; i++)
    {
        scanf(" %u", coin + i);
    }

    sort(coin, coin + N);

    printf("%u\n", getCoinNum(coin, N, K));

    delete coin;
}

u32 getCoinNum(u32* coin, u32 n, u32 sum)
{
    stack<u32> coin_type_stk;
    stack<u32> coin_num_stk;
    u32 k = sum;
    u32 result = 0;

    for (int i = n - 1; i >= 0; i--)
    {
        if (coin[i] <= k)
        {
            u32 n = k / coin[i];
            k -= n * coin[i];
            coin_type_stk.push(i);
            coin_num_stk.push(n);
            break;
        }
    }

    bool flag = false;

    while (k != 0)
    {
        if (coin_type_stk.empty() || coin_num_stk.empty()) throw runtime_error("오류 발생 : 해당 합을 만들 수 없음");
        if (flag)
        {
            if (coin_num_stk.top() == 1)
            {
                if (coin_type_stk.top() != 0)
                {
                    u32 tmp = coin_type_stk.top();
                    coin_type_stk.pop();
                    coin_num_stk.pop();
                    k += coin[tmp];

                    u32 n = k / coin[tmp - 1];
                    k -= n * coin[tmp - 1];
                    coin_type_stk.push(tmp - 1);
                    coin_num_stk.push(n);
                    flag = false;
                }
                else
                {
                    k += coin[coin_type_stk.top()];
                    coin_type_stk.pop();
                    coin_num_stk.pop();
                }
            }
            else
            {
                k += coin[coin_type_stk.top()];
                coin_num_stk.top()--;
                flag = false;
            }
        }
        else
        {
            int i;

            for (i = coin_type_stk.top() - 1; i >= 0; i--)
            {
                if (coin[i] <= k)
                {
                    u32 n = k / coin[i];
                    k -= n * coin[i];
                    coin_type_stk.push(i);
                    coin_num_stk.push(n);
                    break;
                }  
            }

            if (i == -1)
                flag = true;
        }
    }

    while (!coin_num_stk.empty()) result += coin_num_stk.top(), coin_num_stk.pop();

    return result;
}