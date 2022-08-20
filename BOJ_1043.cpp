#include <stdio.h>
#include <vector>
#include <queue>

typedef unsigned int u32;

using namespace std;

void BFS(vector< vector<u32> > vec, bool* know, const u32& start);

int main()
{
    u32 N, M;
    u32** party_arr;
    bool* know;
    u32 init_know_size;
    u32* init_know;
    u32 result = 0;

    scanf(" %u %u", &N, &M);

    vector< vector<u32> > vec;
    vec.resize(N + 1);
    party_arr = new u32*[M];
    know = new bool[N + 1]{ false };

    scanf(" %u", &init_know_size);

    init_know = new u32[init_know_size];

    for (u32 i = 0; i < init_know_size; i++)
    {
        u32 tmp;
        scanf(" %u", &tmp);
        know[tmp] = true;
        init_know[i] = tmp;
    }

    for (u32 i = 0; i < M; i++)
    {
        u32 size;
        scanf(" %u", &size);

        party_arr[i] = new u32[size + 1];
        party_arr[i][0] = size;

        for (u32 j = 1; j <= size; j++)
        {
            scanf(" %u", party_arr[i] + j);
        }

        for (u32 j = 1; j <= size; j++)
        {
            for (u32 k = j + 1; k <= size; k++)
            {
                vec[party_arr[i][j]].push_back(party_arr[i][k]);
                vec[party_arr[i][k]].push_back(party_arr[i][j]);
            }
        }
    }

    for (u32 i = 0; i < init_know_size; i++)
    {
        BFS(vec, know, init_know[i]);
    }

    for (u32 i = 0; i < M; i++)
    {
        bool flag = true;

        for (u32 j = 1; j <= party_arr[i][0]; j++)
        {
            if (know[party_arr[i][j]])
            {
                flag = false;
                break;
            }
        }

        if (flag) result++;
    }

    printf("%u\n", result);

    delete[] party_arr;
    delete[] know;
    delete[] init_know;
}

void BFS(vector< vector<u32> > vec, bool* know, const u32& start)
{
    bool* visited = new bool[vec.size()]{ false };
    queue<u32> que;
    que.push(start);
    visited[start] = true;

    while (!que.empty())
    {
        u32 tmp = que.front();
        que.pop();

        for (u32 i = 0; i < vec[tmp].size(); i++)
        {
            const u32& vertex = vec[tmp][i];

            if(!visited[vertex])
            {
                que.push(vertex);
                visited[vertex] = true;
                know[vertex] = true;
            }
        }
    }
    
    delete[] visited;
}