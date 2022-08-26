#include <cstdio>
#include <vector>
#include <queue>
#include <memory.h>

typedef unsigned int u32;

int main()
{
    u32 N, M;
    u32 num_of_known_real;
    u32 num_of_can_speak_lie = 0;
    bool* real_arr = nullptr;
    u32** party_arr = nullptr;
    std::vector< std::vector<u32> > graph;
    std::queue<u32> que;


    scanf(" %u %u", &N, &M);

    real_arr = new bool[N + 1];
    memset(real_arr, 0x00, (N + 1) * sizeof(bool));
    graph.resize(N + 1);

    scanf(" %u", &num_of_known_real);
    for (size_t i = 0; i < num_of_known_real; i++)
    {
        u32 tmp;
        scanf(" %u", &tmp);

        real_arr[tmp] = true;
        que.push(tmp);
    }

    party_arr = new u32*[M];
    for (size_t i = 0; i < M; i++)
    {
        u32 party_size;

        scanf(" %u", &party_size);

        party_arr[i] = new u32[party_size + 1];
        party_arr[i][0] = party_size;
        for (size_t j = 1; j <= party_size; j++)
        {
            scanf(" %u", party_arr[i] + j);
        }
    }

    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 1; j < party_arr[i][0]; j++)
            graph[party_arr[i][j]].push_back(party_arr[i][j + 1]), graph[party_arr[i][j + 1]].push_back(party_arr[i][j]);
    }

    while(!que.empty())
    {
        u32 v = que.front();
        que.pop();

        for (const u32& next_v : graph[v])
        {
            if(real_arr[next_v] == false)
            {
                real_arr[next_v] = true;
                que.push(next_v);
            }
        }
    }

    for (size_t i = 0; i < M; i++)
    {
        bool flag = true;

        for (size_t j = 1; j <= party_arr[i][0]; j++)
        {
            if(real_arr[party_arr[i][j]] == true)
            {
                flag = false;
                break;
            }
        }

        if (flag)
        {
            num_of_can_speak_lie++;
        }

        delete[] party_arr[i];
    }
    
    delete[] party_arr;
    delete[] real_arr;

    printf("%u\n", num_of_can_speak_lie);
}