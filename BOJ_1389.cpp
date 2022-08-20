#include <iostream>
#include <vector>

typedef unsigned int u32;

using namespace std;

vector<vector<u32>> floydWarshall(const vector<vector<u32>>& vec);

int main()
{
    u32 N, M;
    scanf(" %u %u", &N, &M);

    vector<vector<u32>> vec;
    vec.resize(N + 1);

    for (u32 i = 0; i < M; i++)
    {
        u32 u, v;
        scanf(" %u %u", &u, &v);

        vec[u].push_back(v);
        vec[v].push_back(u);
    }

    u32 min_vertex;
    u32 min_value = 0xFFFFFFFF;
    vector<vector<u32>> result = floydWarshall(vec);

    for (u32 i = 1; i < result.size(); i++)
    {
        u32 sum = 0;
        u32 size = result[i].size();

        for (u32 j = 0; j < size; j++)
        {
            sum += result[i][j];
        }

        if(sum < min_value)
        {
            min_vertex = i;
            min_value = sum;
        }
    }

    printf("%u\n", min_vertex);
}

vector<vector<u32>> floydWarshall(const vector<vector<u32>>& vec)
{
    vector<vector<u32>> dist;
    dist.resize(vec.size());

    for (u32 i = 1; i < vec.size(); i++)
    {
        dist[i].resize(vec.size(), 0x7FFFFFFF);
        dist[i][i] = 0;
    }

    for (u32 i = 1; i < vec.size(); i++)
    {
        for (u32 j = 0; j < vec[i].size(); j++)
        {
            dist[i][vec[i][j]] = 1;
        }
    }

    for (u32 i = 1; i < vec.size(); i++)
    {
        for (u32 j = 1; j < vec.size(); j++)
        {
            for (u32 k = 1; k < vec.size(); k++)
            {
                dist[j][k] = (dist[j][k] < dist[j][i] + dist[i][k])? dist[j][k] : dist[j][i] + dist[i][k];
            }
        }
    }

    return dist;
}