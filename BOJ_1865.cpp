#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>

typedef unsigned int u32;
typedef unsigned long long u64;

using namespace std;

bool isHaveNC(const vector<vector<pair<u32, int>>> &vec);

int main()
{
    u32 TC;

    scanf(" %u", &TC);

    while(TC--)
    {
        u32 N, M, W;

        scanf(" %u %u %u", &N, &M, &W);

        vector<vector<pair<u32, int>>> vec;
        vec.resize(N + 1);

        for (u32 i = 0; i < M; i++)
        {
            u32 S, E, T;

            scanf(" %u %u %u", &S, &E, &T);

            vec[S].push_back({E, T});
            vec[E].push_back({S, T});
        }

        for (u32 i = 0; i < W; i++)
        {
            u32 S, E, T;

            scanf(" %u %u %u", &S, &E, &T);

            vec[S].push_back({E, -T});
        }

        printf("%s\n", (isHaveNC(vec))? "YES" : "NO");
    }
}

bool isHaveNC(const vector<vector<pair<u32, int>>>& vec)
{
    constexpr u32 MAX = 0x7F7F7F7F;

    int *dist = new int[vec.size()];
    memset(dist, 0x7F, vec.size() * sizeof(u32));
    dist[1] = 0;

    queue<u32> que;

    que.push(1);

    for(u32 i = 1; i < vec.size(); i++)
    {
        u32 ret = que.size();

        for (u32 j = 0; j < ret; j++)
        {
            u32 v = que.front();
            que.pop();

            for (u32 k = 0; k < vec[v].size(); k++)
            {
                if (dist[v] + vec[v][k].second < dist[vec[v][k].first])
                {
                    dist[vec[v][k].first] = dist[v] + vec[v][k].second;
                    que.push(vec[v][k].first);
                }
            }
        }
    }

    for (u32 j = 1; j < vec.size(); j++)
    {
        for (u32 k = 0; k < vec[j].size(); k++)
        {
            if (dist[j] + vec[j][k].second < dist[vec[j][k].first])
            {
                delete[] dist;
                return true;
            }
        }
    }

    delete[] dist;

    return false;
}