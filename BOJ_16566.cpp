#include <cstdio>
#include <algorithm>

typedef unsigned int u32;

using namespace std;

u32 getParent(u32* parent, u32 N)
{
    if (parent[N] == N) return N;
    else return parent[N] = getParent(parent, parent[N]);
}

u32 upperBound(u32* arr, u32 size, u32 val)
{
    u32 start = 0;
    u32 end = size - 1;

    while(start < end)
    {
        u32 mid = (start + end) / 2;

        if(arr[mid] > val) end = mid;
        else               start = mid + 1;
    }

    return end;
}

int main()
{
    u32 N, M, K;
    bool* used;
    u32* parent;
    u32* minsu;
    u32* charles;

    scanf(" %u %u %u", &N, &M, &K);

    used = new bool[N + 1]{ false }, parent = new u32[N + 1], minsu = new u32[M], charles = new u32[K];

    for (u32 i = 0; i <= N; i++) parent[i] = i;
    for (u32 i = 0; i < M; i++) scanf(" %u", minsu + i);
    for (u32 i = 0; i < K; i++) scanf(" %u", charles + i);


    sort(minsu, minsu + M);

    for (u32 i = 0; i < K; i++)
    {
        u32 idx = upperBound(minsu, M, getParent(parent, charles[i]));

        if(used[minsu[idx]])
        {
            while (used[minsu[idx]])
            {
                u32 tmp = upperBound(minsu, M, getParent(parent, minsu[idx]));
                parent[getParent(parent, minsu[idx])] = minsu[tmp];

                idx = tmp;
            }
        }

        parent[getParent(parent, charles[i])] = minsu[idx];

        used[minsu[idx]] = true;

        printf("%u\n", minsu[idx]);
    }

    delete[] charles;
    delete[] minsu;
    delete[] parent;
    delete[] used;
}