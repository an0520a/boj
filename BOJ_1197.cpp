#include <stdio.h>
#include <vector>
#include <queue>

typedef unsigned int u32;

using namespace std;

typedef struct _entry
{
    u32 vertex;
    int weight;
} entry;

typedef struct _edge
{
    u32 u;
    u32 v;
    int weight;
} edge;

int getWeightOfMST(const vector< vector<entry> >& graph);

int main()
{
    u32 V, E;
    vector< vector<entry> > graph;

    scanf(" %u %u", &V, &E);

    graph.resize(V + 1);

    for (u32 i = 0; i < E; i++)
    {
        u32 u, v;
        int w;
        scanf(" %u %u %d", &u, &v, &w);

        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    printf("%d\n", getWeightOfMST(graph));
}

int getWeightOfMST(const vector< vector<entry> >& graph)
{
    u32 result = 0;
    bool* visited = new bool[graph.size()]{ false };
    auto cmp = [](const edge& e1, const edge& e2)->bool{ return e1.weight > e2.weight; };
    priority_queue<edge, vector<edge>, decltype(cmp)> que(cmp);
    
    visited[1] = true;
    for (u32 i = 0; i < graph[1].size(); i++)
    {
        que.push({1, graph[1][i].vertex, graph[1][i].weight});
    }

    while(!que.empty())
    {
        edge e = que.top();
        que.pop();

        if(visited[e.v] == false)
        {
            visited[e.v] = true;
            result += e.weight;

            for (u32 i = 0; i < graph[e.v].size(); i++)
            {
                if(visited[graph[e.v][i].vertex] == false) que.push({e.v, graph[e.v][i].vertex, graph[e.v][i].weight});
            }
        }
    }

    delete[] visited;

    return result;
}