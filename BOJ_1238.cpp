#include <stdio.h>
#include <queue>
#include <vector>

typedef unsigned int u32;

typedef struct _entry
{
    u32 vertex;
    u32 weight;
} entry;

using namespace std;

vector<u32> Dijkstra(const vector< vector<entry> > vec, const u32& start);

int main()
{
    u32 N, M, X;
    u32 max_time = 0;
    scanf(" %u %u %u", &N, &M, &X);

    vector< vector<entry> > vec;
    vector< vector<entry> > rev_vec;

    vec.resize(N + 1);
    rev_vec.resize(N + 1);

    for (u32 i = 0; i < M; i++)
    {
        u32 u, v, w;
        scanf(" %u %u %u", &u, &v, &w);

        vec[u].push_back({v, w});
        rev_vec[v].push_back({u, w});
    }

    vector<u32> dist = Dijkstra(vec, X);
    vector<u32> rev_dist = Dijkstra(rev_vec, X);

    for (u32 i = 1; i < vec.size(); i++)
    {
        dist[i] += rev_dist[i];
        max_time = (max_time > dist[i])? max_time : dist[i];
    }

    printf("%u\n", max_time);
    
    return 0;
}

vector<u32> Dijkstra(const vector< vector<entry> > vec, const u32& start)
{
    vector<u32> dist(vec.size(), 0x7FFFFFFF);
    auto cmp = [](const entry& A, const entry& B)->bool{return A.weight > B.weight; };
    priority_queue<entry, vector<entry>, decltype(cmp)> que(cmp);
    que.push({start, 0});
    dist[start] = 0;

    while(!que.empty())
    {
        entry tmp = que.top();
        que.pop();

        for (u32 i = 0; i < vec[tmp.vertex].size(); i++)
        {
            const u32& vertex = vec[tmp.vertex][i].vertex;

            if (tmp.weight + vec[tmp.vertex][i].weight < dist[vertex])
            {
                dist[vertex] = tmp.weight + vec[tmp.vertex][i].weight;
                que.push({vertex, dist[vertex]});
            }
        }
    }

    return dist;
}