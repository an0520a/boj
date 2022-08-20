#include <stdio.h>
#include <vector>

typedef unsigned u32;

using namespace std;

void NM(u32 S, u32 N, u32 M, vector<u32>& vec);

int main()
{
    u32 N, M;
    vector<u32> tmp;

    scanf(" %u %u", &N, &M);

    NM(0, N, M, tmp);
}

void NM(u32 S, u32 N, u32 M, vector<u32>& vec)
{
    if (M == 0)
    {
        for (u32 i = 0; i < vec.size(); i++)
        {
            printf("%u ", vec[i]);
        }
        printf("\n");
    }
    else
    {
        for (u32 i = S + 1; i <= N - (M - 1); i++)
        {
            vec.push_back(i);
            NM(i, N, M - 1, vec);
            vec.pop_back();
        }
    }
}