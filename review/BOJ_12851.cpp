#include <iostream>
#include <queue>
#include <memory.h>

typedef unsigned int u32;

typedef struct StructEntry
{
    int x;
    u32 w;
} Entry;

int main()
{
    std::ios_base::sync_with_stdio(false);

    std::queue<Entry> que;
    u32 dist[100001];
    u32 time = 0;
    size_t count = 0;
    int N, K;
    bool flag = true;

    memset(dist, 0xFF, sizeof(dist));    

    std::cin >> N >> K;

    dist[N] = 0;
    que.push({N, 0});

    while(!que.empty() && flag)
    {
        size_t que_size = que.size();

        for (size_t i = 0; i < que_size; i++)
        {
            Entry entry = que.front();
            que.pop();

            if(entry.x == K)
            {
                count++;
                time = entry.w;
                flag = false;
                continue;
            }

            Entry next_entry_arr[3] = { {entry.x - 1, entry.w + 1}, {entry.x + 1, entry.w + 1}, {entry.x * 2, entry.w + 1} };

            for (size_t i = 0; i < 3; i++)
            {
                const Entry& next_entry = next_entry_arr[i];

                if(next_entry.x < 0 || next_entry.x > 100000) continue;

                if(next_entry.w <= dist[next_entry.x])
                {
                    que.push(next_entry);
                    dist[next_entry.x] = next_entry.w;
                }
            }
        }
    }

    std::cout << time << std::endl;
    std::cout << count << std::endl;
}