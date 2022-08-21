#include <cstdio>
#include <malloc.h>
#include <memory.h>
#include <vector>

typedef unsigned int u32;

using namespace std;

int main()
{
    u32 T;

    scanf(" %u", &T);

    while(T--)
    {
        u32 n;
        u32 result = 0;

        scanf(" %u", &n);

        u32* graph = new u32[n + 1];
        u32* num_arr = new u32[n + 1];
        bool* checked = new bool[n + 1]{ false };
        bool* visited = new bool[n + 1]{ false };

        for (u32 u = 1; u <= n; u++)
        {
            scanf(" %u", graph + u);
        }

        for (u32 i = 1; i <= n; i++)
        {
            if(checked[i] == false)
            {
                vector<u32> vec;

                u32 num = 1;
                u32 v = i;
                vec.push_back(v);
                visited[v] = true;
                num_arr[v] = 1;

                while(visited[graph[v]] == false && checked[graph[v]] == false)
                {
                    v = graph[v];
                    visited[v] = true;
                    vec.push_back(v);
                    num++;
                    num_arr[v] = num;
                }

                if(checked[graph[v]]) result += num;
                else                  result += num_arr[graph[v]] - 1;

                for (u32 j = 0; j < vec.size(); j++) visited[vec[j]] = false;
                for (u32 j = 0; j < vec.size(); j++) checked[vec[j]] = true;
            }
        }

        printf("%u\n", result);

        delete[] graph;
        delete[] checked;
        delete[] visited;
    }
}