#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#pragma GCC optimize ("prefetch-loop-arrays")

#include <iostream>
#include <algorithm>
#include <queue>

enum class FunctionCode
{
    NaN = 0,
    Start = 1,
    D = 'D',
    S = 'S',
    L = 'L',
    R = 'R'
};

unsigned int RegisterFunctionD(unsigned int _val)
{
    return 2 * _val % 10000;
}

unsigned int RegisterFunctionS(unsigned int _val)
{
    if (_val == 0)  return 9999;
    else            return _val - 1;
}

unsigned int RegisterFunctionL(unsigned int _val)
{
    _val *= 10;
    return (_val % 10000) + (_val / 10000);
}

unsigned int RegisterFunctionR(unsigned int _val)
{
    return (_val / 10) + (_val % 10) * 1000;
}

int main()
{
    size_t T;

    std::cin >> T;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    for (size_t i = 0; i < T; i++)
    {
        unsigned int A, B;
        std::queue<unsigned int> que;

        bool visited[10000];
        unsigned int before_num[10000] = { 0 };
        FunctionCode before_function[10001] = { FunctionCode::NaN };

        std::cin >> A >> B;

        before_function[A] = FunctionCode::Start;
        que.push(A);

        while (!que.empty())
        {
            unsigned int val = que.front();
            que.pop();

            if (val == B)
            {
                break;
            }

            unsigned int next_val;

            next_val = RegisterFunctionD(val);
            if(before_function[next_val] == FunctionCode::NaN)
            {
                before_function[next_val] = FunctionCode::D;
                before_num[next_val] = val;
                que.push(next_val);
            }

            next_val = RegisterFunctionS(val);
            if(before_function[next_val] == FunctionCode::NaN)
            {
                before_function[next_val] = FunctionCode::S;
                before_num[next_val] = val;
                que.push(next_val);
            }

            next_val = RegisterFunctionL(val);
            if(before_function[next_val] == FunctionCode::NaN)
            {
                before_function[next_val] = FunctionCode::L;
                before_num[next_val] = val;
                que.push(next_val);
            }

            next_val = RegisterFunctionR(val);
            if(before_function[next_val] == FunctionCode::NaN)
            {
                before_function[next_val] = FunctionCode::R;
                before_num[next_val] = val;
                que.push(next_val);
            }
        }

        std::string result;

        unsigned int v = B;
        while (before_function[v] != FunctionCode::Start)
        {
            result.push_back(static_cast<char>(before_function[v]));
            v = before_num[v];
        }

        std::reverse(result.begin(), result.end());

        std::cout << result << '\n';
        
    }
}