#include <stdio.h>

typedef unsigned int u32;

void preToPost(u32* preBegin, u32* preEnd);

int main()
{
    u32 arr[10001];
    u32 size = 0;

    while (1)
    {
        if (scanf(" %u", &arr[size]) == EOF) { break; }
        size++;
    }
    
    preToPost(arr, &arr[0] + size);
}

void preToPost(u32* preBegin, u32* preEnd)
{
    u32* leftBegin = preBegin + 1;
    u32* leftEnd = preEnd;
    u32* rightBegin = preEnd;
    u32* rightEnd = preEnd;

    u32 root = *preBegin;

    for (u32* p = preBegin; p < preEnd; p++)
    {
        if(*p > root) { leftEnd = p, rightBegin = p; break; }
    }

    if (leftBegin < leftEnd)
    {
        preToPost(leftBegin, leftEnd);
    }
    if (rightBegin < rightEnd)
    {
        preToPost(rightBegin, rightEnd);
    }

    printf("%u\n", root);
}