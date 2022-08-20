#include <cstdio>
#include <stack>
#include <malloc.h>

typedef unsigned int u32;

int main()
{
    u32 N;
    u32 *arr;
    int *ans;
    char *ansArr;
    u32 ansArrSize = 0;
    u32 ansArrCapacity = 100;
    u32 count[1000001] = { 0 };
    std::stack<u32> stk;

    scanf(" %u", &N);

    arr = new u32[N];
    ans = new int[N];
    ansArr = (char *)malloc(101 * sizeof(char));

    for (u32 i = 0; i < N; i++)
    {
        scanf(" %u", arr + i);
        count[arr[i]]++;
    }

    for (int i = N - 1; i >= 0; i--)
    {
        while(!stk.empty() && count[stk.top()] <= count[arr[i]]) stk.pop();
        
        if(stk.empty()) ans[i] = -1;
        else            ans[i] = (int)stk.top();

        stk.push(arr[i]);
    }

    char tmpS[7];
    for (u32 i = 0; i < N; i++)
    {
        if(ans[i] == -1) ansArr[ansArrSize] = '-', ansArr[ansArrSize + 1] = '1', ansArr[ansArrSize + 2] = ' ', ansArrSize += 3;
        else
        {
            u32 tmp = ans[i];
            u32 tmpSize = 0;

            do
            {
                tmpS[6 - tmpSize] = tmp % 10 + '0';
                tmp /= 10;
                tmpSize++;
            } while (tmp);

            for (u32 s = 7 - tmpSize, i = 0; i < tmpSize; i++)
            {
                ansArr[ansArrSize + i] = tmpS[s + i];
            }
            ansArr[ansArrSize + tmpSize] = ' ';

            ansArrSize += tmpSize + 1;
        }

        if(ansArrSize > ansArrCapacity - 10)
        {
            ansArr = (char *)realloc(ansArr, ansArrCapacity * 2 + 1);
            ansArrCapacity *= 2;
        }
    }
    ansArr[ansArrSize] = '\0';

    printf("%s\n", ansArr);

    free(ansArr);
    delete[] ans;
    delete[] arr;
}