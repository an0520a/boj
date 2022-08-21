#include <cstdio>
#include <stack>

typedef unsigned int u32;

int main()
{
    u32 N, K;
    u32 ansSize;
    u32 *arr;
    char *str;
    std::stack<u32> stk;

    scanf(" %u %u", &N ,&K);

    ansSize = N - K;
    str = new char[N + 1];

    scanf(" %s", str);

    arr = new u32[N];
    for (u32 i = 0; i < N; i++)
    {
        arr[i] = str[i] - '0';
    }

    for (u32 i = 0; i < N; i++)
    {
        while(!stk.empty() && stk.top() < arr[i] && ansSize < stk.size() + N - i) stk.pop();
        
        if(stk.size() != ansSize) stk.push(arr[i]);
    }

    str[ansSize] = 0;
    for (int i = ansSize - 1; i >= 0; i--) str[i] = stk.top() + '0', stk.pop();
    printf("%s\n", str);

    delete[] arr;
    delete[] str;
}