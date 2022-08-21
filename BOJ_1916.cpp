#include <iostream>
#include <queue>
#include <vector>

typedef unsigned int u32;

typedef struct _entry
{
    u32 dest;
    u32 weight;
} entry;

using namespace std;

vector<u32> Dijkstra(const vector<vector<entry>> vec, const u32& start);

int main()
{
    u32 N, M;
    u32 start, end;
    scanf(" %u", &N);
    scanf(" %u", &M);

    vector<vector<entry>> vec;
    vec.resize(N + 1);

    while (M--)
    {
        u32 org, dest, weight;
        scanf(" %u %u %u", &org, &dest, &weight);

        vec[org].push_back({dest, weight});
    }
    scanf(" %u %u", &start, &end);

    vector<u32> result = Dijkstra(vec, start);
    printf("%u\n", result[end]);
}

vector<u32> Dijkstra(const vector<vector<entry>> vec, const u32& start)
{
    vector<u32> dist(vec.size(), 0xFFFFFFFF);

    auto cmp = [](const entry& a, const entry &b)->bool{ return a.weight > b.weight; };

    priority_queue<entry, vector<entry>, decltype(cmp)> que(cmp);

    dist[start] = 0;
    que.push({start, 0});

    while (!que.empty())
    {
        entry pre = que.top();
        que.pop();

        if(pre.weight <= dist[pre.dest])
        {
            const u32& vertex = pre.dest;

            for (u32 i = 0; i < vec[vertex].size(); i++)
            {
                if (pre.weight + vec[vertex][i].weight < dist[vec[vertex][i].dest])
                {
                    dist[vec[vertex][i].dest] = pre.weight + vec[vertex][i].weight;
                    que.push({vec[vertex][i].dest, dist[vec[vertex][i].dest]});
                }
            }
        }
    }

    return dist;
}