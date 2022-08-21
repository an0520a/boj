#include <stdio.h>
#include <vector>
#include <memory.h>

typedef unsigned int u32;

typedef struct _entry
{
    u32 vertex;
    u32 weight;
} entry;

using namespace std;

void floydWarshall(const vector< vector<entry> > vec);

int main()
{
    u32 N;
    u32 M;
    vector< vector<entry> > vec;

    scanf(" %u", &N);
    scanf(" %u", &M);

    vec.resize(N + 1);

    for (u32 i = 0; i < M; i++)
    {
        u32 u, v, w;

        scanf(" %u %u %u", &u, &v, &w);

        vec[u].push_back({v, w});
    }

    floydWarshall(vec);
}

void floydWarshall(const vector< vector<entry> > vec)
{
    u32** dist = new u32*[vec.size()];
    for (u32 i = 1; i < vec.size(); i++) 
    {
        dist[i] = new u32[vec.size()]{};
        memset(dist[i], 0x7F, vec.size() * sizeof(u32));
    }

    for (u32 i = 1; i < vec.size(); i++)
    {
        dist[i][i] = 0;

        for (u32 j = 0; j < vec[i].size(); j++)
        {
            const entry& tmp = vec[i][j];
            dist[i][tmp.vertex] = (dist[i][tmp.vertex] < tmp.weight)? dist[i][tmp.vertex] : tmp.weight;
        }
    }

    for (u32 k = 1; k < vec.size(); k++)
    {
        for (u32 i = 1; i < vec.size(); i++)
        {
            for (u32 j = 1; j < vec.size(); j++)
            {
                dist[i][j] = ((dist[i][k] + dist[k][j]) < dist[i][j])? (dist[i][k] + dist[k][j]) : dist[i][j];
            }
        }
    }

    for (u32 i = 1; i < vec.size(); i++)
    {
        for (u32 j = 1; j < vec.size(); j++)
        {
            printf("%u ", (dist[i][j] == 0x7F7F7F7F)? 0 : dist[i][j]);
        }
        printf("\n");
    }

    for (u32 i = 1; i < vec.size(); i++) 
    {
        delete[] dist[i];
    }
    delete[] dist;
}