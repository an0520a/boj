#include <stdio.h>
#include <memory.h>
#include <vector>
#include <algorithm>

typedef int u32;

using namespace std;

int main()
{
    u32 N, M;
    u32* arr;
    vector<u32> num;
    vector<u32> sequence;
    bool flag = false;

    scanf(" %u %u", &N, &M);

    arr = new u32[N];
    for (u32 i = 0; i < N; i++)
    {
        scanf(" %u", arr + i);
    }

    sort(arr, arr + N);

    num.push_back(arr[0]);
    for (u32 i = 1; i < N; i++)
    {
        if (num.back() != arr[i]) num.push_back(arr[i]);
    }
        
    sequence.push_back(0);
    
    while(!sequence.empty())
    {
        if (sequence.back() == num.size())
        {
            sequence.pop_back();
            flag = true;
        }
        else if (flag)
        {
            sequence.back()++;
            flag = false;
        }
        else
        {
            if (sequence.size() == M)
            {
                for (u32 i = 0; i < M; i++) printf("%u ", num[sequence[i]]);
                printf("\n");
                flag = true;
            }
            else sequence.push_back(sequence.back());
        }
    }

    delete[] arr;
}