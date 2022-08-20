#include <cstdio>
#include <queue>
#include <algorithm>

typedef struct _line
{
    int u;
    int v;
} line;

typedef unsigned int u32;

using namespace std;

int main()
{
    int N;
    int d;
    int start = 0x7FFFFFFF, end = 0x80000000;
    u32 max = 0;
    line* arr;
    auto cmp = [](const int& x, const int& y)->bool{ return x > y; };
    priority_queue<int, vector<int>, decltype(cmp)> que(cmp); 

    scanf(" %d", &N);

    arr = new line[N];
    for (u32 i = 0; i < N; i++)
    {
        int h, o;

        scanf(" %d %d", &h, &o);

        if(h > o)
        {
            int tmp = h;
            h = o;
            o = tmp;
        }

        arr[i].u = h, arr[i].v = o;
        start = (start < h)? start : h, end = (end > o)? end : o;
    }

    scanf(" %d", &d);

    sort(arr, arr + N, [](const line& l1, const line& l2)->bool{ return (l1.v == l2.v)? l1.u > l2.u : l1.v < l2.v; });
    for (int i = 0, k = start; i < N;)
    {
        if(arr[i].v <= k + d && arr[i].u >= k) que.push(arr[i].u), i++;
        else
        {
            k++;
            if (k > end - d) break;
            while(!que.empty() && que.top() < k) que.pop();
        }
        max = (max > que.size())? max : que.size();
    }
    
    delete[] arr;

    printf("%u\n", max);
}