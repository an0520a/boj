#include <cstdio>
#include <malloc.h>
#include <stack>

typedef unsigned int u32;

int main()
{
    u32 N;
    u32* arr;
    std::stack<u32> stk;

    scanf(" %u", &N);

    arr = (u32 *)malloc(N * sizeof(u32));
    for (u32 i = 0; i < N; i++) scanf(" %u", arr + i);

    for (u32 i = 0; i < N; i++)
    {
        while(!stk.empty() && arr[stk.top()] < arr[i]) stk.pop();
        
        if(!stk.empty()) printf("%u ", stk.top() + 1);
        else                             printf("0 ");

        while(!stk.empty() && arr[stk.top()] == arr[i]) stk.pop();

        stk.push(i);
    }

    free(arr);
}