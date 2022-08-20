#include <cstdio>
#include <stack>

typedef unsigned int u32;

int main()
{
    u32 N;
    u32 *arr;
    int *ans;
    std::stack<u32> stk;

    scanf(" %u", &N);

    arr = new u32[N];
    ans = new int[N];
    for (u32 i = 0; i < N; i++) scanf(" %u", arr + i);

    for (int i = N - 1; i >= 0; i--)
    {
        while(!stk.empty() && stk.top() <= arr[i]) stk.pop();

        if(stk.empty()) ans[i] = -1;
        else            ans[i] = (int)stk.top();

        stk.push(arr[i]);
    }

    for (u32 i = 0; i < N; i++) printf("%d ", ans[i]);
    printf("\n");

    delete[] ans;
    delete[] arr;
}