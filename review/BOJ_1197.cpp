#include <cstdio>
#include <vector>
#include <queue>
#include <memory.h>

typedef unsigned int u32;
typedef int i32;
typedef unsigned long long u64;
typedef long long i64;

typedef struct StructGraphEntry
{
    u32 vertex;
    i32 weight;
} GraphEntry;

typedef struct StructGraphEdge
{
    u32 vertex1;
    u32 vertex2;
    i32 weight;
} GraphEdge;

i32 GetWeightSumMstByPrim(const std::vector< std::vector<GraphEntry> >& graph);
i32 GetWeightSumMstByKruskal(const std::vector< std::vector<GraphEntry> >& graph);

int main()
{
    u32 V, E;
    std::vector< std::vector<GraphEntry> > graph;

    scanf(" %u %u", &V, &E);

    graph.resize(V + 1);

    for (size_t i = 0; i < E; i++)
    {
        u32 A, B;
        i32 C;

        scanf(" %u %u %d", &A, &B, &C);

        graph[A].push_back({B, C});
        graph[B].push_back({A, C});
    }

    printf("%d\n", GetWeightSumMstByKruskal(graph));
}

i32 GetWeightSumMstByPrim(const std::vector< std::vector<GraphEntry> >& graph)
{
    bool* visited = new bool[graph.size()];
    memset(visited, 0x00, graph.size() * sizeof(bool));
    i32 mst_weight_sum = 0;

    auto graph_entry_cmp = [](const GraphEntry& x, const GraphEntry& y)->bool{ return x.weight > y.weight; };
    std::priority_queue<GraphEntry, std::vector<GraphEntry>, decltype(graph_entry_cmp)> que(graph_entry_cmp);

    visited[1] = true;
    for (const GraphEntry& edge : graph[1]) que.push(edge);

    while(!que.empty())
    {
        GraphEntry edge = que.top();
        que.pop();

        if(visited[edge.vertex] == false)
        {
            visited[edge.vertex] = true;
            mst_weight_sum += edge.weight;

            for(const GraphEntry& next_edge : graph[edge.vertex])
            {
                if(visited[next_edge.vertex] == false) que.push(next_edge);
            }
        }
    }

    delete[] visited;

    return mst_weight_sum;
}

class UnionFind
{
public:
    static u32 find(u32* union_find_parent_arr, const u32& x)
    {
        if(union_find_parent_arr[x] != x)
        {
            return union_find_parent_arr[x] = find(union_find_parent_arr, union_find_parent_arr[x]);
        }
        else
        {
            return x;
        }
    }
    static void SetParent(u32* union_find_parent_arr, const u32& parent, const u32& child)
    {
        union_find_parent_arr[find(union_find_parent_arr, child)] = find(union_find_parent_arr, parent);
    }
};

i32 GetWeightSumMstByKruskal(const std::vector< std::vector<GraphEntry> >& graph)
{
    u32* union_find_parent_arr = new u32[graph.size()];
    for (u32 i = 1; i < graph.size(); i++) union_find_parent_arr[i] = i;
    i32 mst_weight_sum = 0;

    auto graph_entry_cmp = [](const GraphEdge& x, const GraphEdge& y)->bool{ return x.weight > y.weight; };
    std::priority_queue<GraphEdge, std::vector<GraphEdge>, decltype(graph_entry_cmp)> que(graph_entry_cmp);

    for (u32 i = 1; i < graph.size(); i++)
    {
        for (const GraphEntry& edge : graph[i])
        {
            que.push({i, edge.vertex, edge.weight});
        }
    }

    u32 edge_count = 0;

    while(edge_count != graph.size() - 2 && !que.empty())
    {
        GraphEdge edge = que.top();
        que.pop();

        if(UnionFind::find(union_find_parent_arr, edge.vertex1) != UnionFind::find(union_find_parent_arr, edge.vertex2))
        {
            mst_weight_sum += edge.weight;
            UnionFind::SetParent(union_find_parent_arr, edge.vertex1, edge.vertex2);
            edge_count++;
        }
    }

    delete union_find_parent_arr;

    return mst_weight_sum;
}