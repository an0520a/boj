#include <stdio.h>
#include <queue>
#include <vector>
#include <memory.h>

typedef unsigned int u32;

using namespace std;

typedef struct _point
{
    u32 y;
    u32 x;
} point;

u32 BFS(u32** arr, u32 size);

int main()
{
    u32 N;
    u32** arr;

    scanf(" %u", &N);

    arr = new u32*[N];
    for (u32 i = 0; i < N; i++)
    {
        arr[i] = new u32[N];

        for (u32 j = 0; j < N; j++)
        {
            scanf(" %u", arr[i] + j);
        }
    }

    printf("%u\n", BFS(arr, N));

    for (u32 i = 0; i < N; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}

u32 BFS(u32** arr, u32 size)
{
    u32 time = 0;
    u32 sharkSize = 2;
    point sharkPos;
    u32 sharkAte = 0;

    queue<point> que;
    priority_queue<u32, vector<u32>, greater<u32>> fish; // 불통과시 수정

    bool** visited = new bool*[size];
    for (u32 i = 0; i < size; i++) visited[i] = new bool[size];

    for (u32 i = 0; i < size; i++)
    {
        for (u32 j = 0; j < size; j++)
        {
            if (arr[i][j] == 9)
            {
                sharkPos = {i, j};
                arr[i][j] = 0;
            }
            else if (arr[i][j] != 0)
            {
                fish.push(arr[i][j]);
            }
        }
    }

    bool flag = true;

    while (!fish.empty() && fish.top() < sharkSize && flag)
    {
        flag = false;
        for (u32 i = 0; i < size; i++) memset(visited[i], false, size * sizeof(bool));
        que.push(sharkPos);
        visited[sharkPos.y][sharkPos.x] = true;
        u32 dist = 0;
        auto cmp = [](point A, point B)->bool{ return (A.y != B.y)? A.y > B.y : (A.x > B.x); };
        priority_queue<point, vector<point>, decltype(cmp)> p_que(cmp);

        while (!que.empty())
        {
            u32 queSize = que.size();
            dist++;
            
            for (u32 i = 0; i < queSize; i++)
            {
                point p = que.front();
                que.pop();

                if (p.y != 0 && visited[p.y - 1][p.x] == false && arr[p.y - 1][p.x] <= sharkSize)
                {
                    if   (arr[p.y - 1][p.x] > 0 && arr[p.y - 1][p.x] < sharkSize) p_que.push({p.y - 1, p.x});
                    else                                                            que.push({p.y - 1, p.x});

                    visited[p.y - 1][p.x] = true;
                }
                if (p.x != 0 && visited[p.y][p.x - 1] == false && arr[p.y][p.x - 1] <= sharkSize)
                {
                    if   (arr[p.y][p.x - 1] > 0 && arr[p.y][p.x - 1] < sharkSize) p_que.push({p.y, p.x - 1});
                    else                                                            que.push({p.y, p.x - 1});

                    visited[p.y][p.x - 1] = true;
                }
                if (p.x != size - 1 && visited[p.y][p.x + 1] == false && arr[p.y][p.x + 1] <= sharkSize)
                {
                    if   (arr[p.y][p.x + 1] > 0 && arr[p.y][p.x + 1] < sharkSize) p_que.push({p.y, p.x + 1});
                    else                                                            que.push({p.y, p.x + 1});
                    
                    visited[p.y][p.x + 1] = true;
                }
                if (p.y != size - 1 && visited[p.y + 1][p.x] == false && arr[p.y + 1][p.x] <= sharkSize)
                {
                    if   (arr[p.y + 1][p.x] > 0 && arr[p.y + 1][p.x] < sharkSize) p_que.push({p.y + 1, p.x});
                    else                                                            que.push({p.y + 1, p.x});
                    
                    visited[p.y + 1][p.x] = true;
                }
            }

            if (!p_que.empty())
            {
                point p = p_que.top();
                sharkPos = {p.y, p.x};
                sharkAte++;
                arr[p.y][p.x] = 0;
                time += dist;
                fish.pop();
                queue<point> tmp;
                que.swap(tmp);
                flag = true;
            }

            if (sharkSize == sharkAte) { sharkSize++; sharkAte = 0; }
        }
    }

    for (u32 i = 0; i < size; i++) delete[] visited[i];
    delete[] visited;

    return time;
}