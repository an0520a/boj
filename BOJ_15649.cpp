#include <stdio.h>
#include <malloc.h>
#include <vector>

typedef unsigned int u32;

using namespace std;

template<typename T>
vector< vector<T> > combination(T* sequence, u32 size, u32 k);

int main()
{
    u32 N, M;
    u32 arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    scanf(" %u %u", &N, &M);

    vector< vector<u32> > c = combination(arr, N, M);

    for (u32 i = 0; i < c.size(); i++)
    {
        for (u32 j = 0; j < c[i].size(); j++)
        {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
}

template<typename T>
vector< vector<T> > combination(T* sequence, u32 size, u32 k)
{
    vector< vector<T> > tmp;
    vector< vector<T> > result;

    if (k == 1)
    {
        result.resize(size);

        for (u32 i = 0; i < size; i++)
        {
            result[i].push_back(sequence[i]);
        }

        return result;
    }
    else
    {
        for (u32 i = 0; i <= size - k; i++)
        {
            u32 r = result.size();
            tmp = combination(sequence + (i + 1), size - (i + 1), k - 1);

            result.resize(r + tmp.size());

            for (u32 j = 0; j < tmp.size(); j++)
            {
                result[r].push_back(sequence[i]);
                result[r].insert(result[r].end(), tmp[j].begin(), tmp[j].end());
                r++;
            }
        }
    }

    return result;
}