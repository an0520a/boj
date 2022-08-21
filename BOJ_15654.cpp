#include <stdio.h>
#include <vector>
#include <algorithm>

typedef unsigned u32;

using namespace std;

void NM(u32 S, u32 N, u32 M, vector<u32>& vec, const vector<u32>& num);

int main()
{
    u32 N, M;
    vector<u32> num;
    vector<u32> tmp;

    scanf(" %u %u", &N, &M);

    num.resize(N + 1);

    num[0] = 0;
    for (u32 i = 1; i <= N; i++) scanf(" %u", &num[i]);

    sort(num.begin(), num.end());

    NM(0, N, M, tmp, num);
}

void NM(u32 S, u32 N, u32 M, vector<u32>& vec, const vector<u32>& num)
{
    static bool visited[9] = { false };

    if (M == 0)
    {
        for (u32 i = 0; i < vec.size(); i++)
        {
            printf("%u ", num[vec[i]]);
        }
        printf("\n");
    }
    else
    {
        for (u32 i = 1; i <= N; i++)
        {
            if (visited[i] == false)
            {
                vec.push_back(i);
                visited[i] = true;
                NM(i, N, M - 1, vec, num);
                visited[i] = false;
                vec.pop_back();
            }
        }
    }
}