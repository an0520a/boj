#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>

typedef unsigned int u32;

using namespace std;

vector<u32> DFS(const vector<vector<u32>>& vec, const u32& start);
vector<u32> BFS(const vector<vector<u32>>& vec, const u32& start);

int main()
{
    u32 N, M, V;

    scanf(" %u %u %u", &N, &M, &V);

    vector<vector<u32>> vec;
    vec.resize(N + 1);

    for (u32 i = 0; i < M; i++)
    {
        u32 u, v;
        scanf(" %u %u", &u, &v);

        vec[u].push_back(v);
        vec[v].push_back(u);
    }

    for (u32 i = 1; i <= N; i++)
    {
        sort(vec[i].begin(), vec[i].end());
    }

    vector<u32> DFS_result = DFS(vec, V);
    u32 DFS_size = DFS_result.size();

    for (u32 i = 0; i < DFS_size; i++) printf("%u ", DFS_result[i]);
    printf("\n");

    { vector<u32> tmp; DFS_result.swap(tmp); }

    vector<u32> BFS_result = BFS(vec, V);
    u32 BFS_size = BFS_result.size();

    for (u32 i = 0; i < DFS_size; i++) printf("%u ", BFS_result[i]);
    printf("\n");

    { vector<u32> tmp; BFS_result.swap(tmp); }

}

vector<u32> DFS(const vector<vector<u32>>& vec, const u32& start)
{
    u32* index = new u32[vec.size()]{ 0 };
    bool* visited = new bool[vec.size()] { 0 };
    vector<u32> result;
    
    stack<u32> stk;
    stk.push(start);
    result.push_back(start);
    visited[start] = true;

    while(!stk.empty())
    {
        u32 vertex = stk.top();
        u32 size = vec[vertex].size();
        u32 i;
        bool flag = true;

        for (i = index[vertex]; i < size; i++)
        {
            const u32& dest = vec[vertex][i];

            if (visited[dest] == false)
            {
                visited[dest] = true;
                stk.push(dest);
                result.push_back(dest);
                index[vertex] = i;
                flag = false;
                break;
            }
        }

        if (flag) stk.pop();
    }

    delete[] index;
    delete[] visited;

    return result;
}

vector<u32> BFS(const vector<vector<u32>>& vec, const u32& start)
{
    bool* visited = new bool[vec.size()] { 0 };
    vector<u32> result;
    
    queue<u32> que;
    que.push(start);
    result.push_back(start);
    visited[start] = true;

    while(!que.empty())
    {
        u32 vertex = que.front(); que.pop();
        u32 size = vec[vertex].size();

        for (u32 i = 0; i < size; i++)
        {
            const u32& dest = vec[vertex][i];

            if (visited[dest] == false)
            {
                que.push(dest);
                result.push_back(dest);
                visited[dest] = true;
            }
        }
    }

    delete[] visited;

    return result;
}