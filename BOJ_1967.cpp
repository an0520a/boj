#include <stdio.h>
#include <memory.h>
#include <vector>
#include <stack>

typedef unsigned int u32;

using namespace std;

typedef struct _entry
{
    u32 vertex;
    u32 weight;
} entry;

u32 getTreeDiameter(const vector< vector<entry> >& vec);

int main()
{
    u32 n;
    scanf(" %u", &n);

    vector< vector<entry> > vec;
    vec.resize(n);

    for (u32 i = 1; i < n; i++)
    {
        u32 u, v, w;
        scanf(" %u %u %u", &u, &v, &w);

        vec[u - 1].push_back({v - 1, w});
        vec[v - 1].push_back({u - 1, w});
    }

    printf("%u\n", getTreeDiameter(vec));
}

u32 getTreeDiameter(const vector< vector<entry> >& vec)
{
    bool* visited = new bool[vec.size()]{ 0 };
    u32* index = new u32[vec.size()]{ 0 };
    entry max_node = {0, 0};

    stack<entry> stk;
    visited[max_node.vertex] = true;
    stk.push(max_node);

    while(!stk.empty())
    {
        const entry tmp = stk.top();
        bool flag = true;

        max_node = ((max_node.weight > tmp.weight)? max_node : tmp);
        
        for (u32 i = index[tmp.vertex]; i < vec[tmp.vertex].size(); i++)
        {
            const entry& next = vec[tmp.vertex][i];

            if (!visited[next.vertex])
            {
                visited[next.vertex] = true;
                stk.push({next.vertex, tmp.weight + next.weight});
                index[tmp.vertex] = i + 1;
                flag = false;
                break;
            }
        }

        if (flag) stk.pop();
    }

    memset(visited, 0, vec.size() * sizeof(bool));
    memset(index, 0, vec.size() * sizeof(u32));
    max_node.weight = 0;
    visited[max_node.vertex] = true;
    stk.push(max_node);

    while(!stk.empty())
    {
        const entry tmp = stk.top();
        bool flag = true;

        max_node = ((max_node.weight > tmp.weight)? max_node : tmp);
        
        for (u32 i = index[tmp.vertex]; i < vec[tmp.vertex].size(); i++)
        {
            const entry& next = vec[tmp.vertex][i];

            if (!visited[next.vertex])
            {
                stk.push({next.vertex, tmp.weight + next.weight});
                visited[next.vertex] = true;
                index[tmp.vertex] = i + 1;
                flag = false;
                break;
            }
        }

        if (flag) stk.pop();
    }

    delete[] visited;
    delete[] index;
    return max_node.weight;
}