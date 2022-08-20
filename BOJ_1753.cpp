#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef unsigned int u32;

typedef struct _entry
{
    u32 vertex;
    u32 weight;
} entry;

vector<u32> Dijkstra(const vector<vector<entry>>& vec, const u32& start);

int main()
{
    u32 V, E, start;
    scanf(" %u %u", &V, &E);
    scanf(" %u", &start);

    vector<vector<entry>> vec;
    vec.resize(V + 1);

    for (u32 i = 0; i < E; i++)
    {
        u32 org, dest, weight;
        scanf(" %u %u %u", &org, &dest, &weight);

        vec[org].push_back({dest, weight});
    }

    vector<u32> result = Dijkstra(vec, start);

    for (u32 i = 1; i < result.size(); i++)
    {
        if(result[i] != 0xFFFFFFFF) printf("%u\n", result[i]);
        else                        printf("INF\n");
    }
}

vector<u32> Dijkstra(const vector<vector<entry>>& vec, const u32& start)
{
    vector<u32> dist(vec.size(), 0xFFFFFFFF);
    auto cmp = [](const entry& x, const entry& y)->bool{ return x.weight > y.weight; };
    priority_queue<entry, vector<entry>, decltype(cmp)> que(cmp);

    que.push({start, 0});
    dist[start] = 0;

    while(!que.empty())
    {
        entry tmp = que.top();
        que.pop();

        if (tmp.weight <= dist[tmp.vertex])
        {
            u32 size = vec[tmp.vertex].size();

            for (u32 i = 0; i < size; i++)
            {
                if (tmp.weight + vec[tmp.vertex][i].weight < dist[vec[tmp.vertex][i].vertex])
                {
                    dist[vec[tmp.vertex][i].vertex] = tmp.weight + vec[tmp.vertex][i].weight;
                    que.push({vec[tmp.vertex][i].vertex, dist[vec[tmp.vertex][i].vertex]});
                }
            }
        }
    }

    return dist;
}