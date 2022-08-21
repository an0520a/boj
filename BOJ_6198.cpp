#include <cstdio>
#include <stack>

typedef unsigned int u32;
typedef unsigned long long u64;

int main()
{
    u32 N;
    u32* arr;
    u64 sum = 0;
    std::stack<u32> stk;

    scanf(" %u", &N);

    arr = new u32[N];
    for (u32 i = 0; i < N; i++) scanf(" %u", arr + i);

    for (u32 i = 0; i < N; i++)
    {
        while(!stk.empty() && arr[stk.top()] <= arr[i]) sum += i - stk.top() - 1, stk.pop();
        stk.push(i);
    }
    while(!stk.empty()) sum += (N - 1) - stk.top(), stk.pop();

    printf("%llu\n", sum);
}