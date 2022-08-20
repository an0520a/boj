#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

typedef unsigned int u32;

typedef struct _point
{
    double x;
    double y;
} point;

typedef struct _entry
{
    u32 vertex;
    double weight;
} entry;

double getMinCost(point* arr, u32 size);

int main()
{
    u32 N;
    scanf(" %u", &N);

    point* arr = new point[N];

    for (u32 i = 0; i < N; i++)
    {
        scanf(" %lf %lf", &arr[i].x, &arr[i].y);
    }

    printf("%.2lf\n", getMinCost(arr, N));

    delete[] arr;
}

double getMinCost(point* arr, u32 size)
{
    bool* visited = new bool[size]{ 0 };
    auto cmp = [](const entry& x, const entry& y)->bool{ return x.weight > y.weight; };
    auto dist = [](const point& p1, const point& p2)->double{ return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)); };
    double cost_sum = 0;
    u32 count = 0;
    priority_queue<entry, vector<entry>, decltype(cmp)> que(cmp);

    que.push({0, 0});

    while(!que.empty() && count != size)
    {
        entry tmp = que.top();
        que.pop();

        if(visited[tmp.vertex] == false)
        {
            visited[tmp.vertex] = true;
            cost_sum += tmp.weight;
            count++;

            for (u32 i = 0; i < size; i++)
            {
                if(visited[i] == false)
                {
                    que.push({i, dist(arr[tmp.vertex], arr[i])});
                }
            }
        }
    }

    delete[] visited;

    return cost_sum;
}