#include <cstdio>
#include <malloc.h>

typedef unsigned short u16;
typedef unsigned int u32;
class Point
{
public:
    Point() {}
    Point(u16 _y, u16 _x) : y(_y), x(_x) {}
    bool operator==(const Point& p) const { return y == p.y && x == p.x; }
    bool operator!=(const Point& p) const { return y != p.y || x != p.x; }
    u16 y;
    u16 x;
};

Point getParent(Point** parentArr, Point p)
{
    if(p == parentArr[p.y][p.x]) return p;
    else
    {
        return parentArr[p.y][p.x] = getParent(parentArr, parentArr[p.y][p.x]);
    }
}

int main()
{
    u32 N, M;
    u32 count = 0;
    Point **parent;
    
    scanf(" %u %u", &N, &M);

    char (*graph)[M + 1] = (char (*)[M + 1])malloc(N * (M + 1) * sizeof(char));

    parent = new Point*[N];
    for (u16 i = 0; i < N; i++)
    {
        scanf(" %s", graph[i]);
        parent[i] = new Point[M];
        for (u16 j = 0; j < M; j++) parent[i][j] = {i, j};
    }

    for (u16 i = 0; i < N; i++)
    {
        for (u16 j = 0; j < M; j++)
        {
            if(parent[i][j].y == i  && parent[i][j].x == j)
            {
                Point p = {i, j};

                while (true)
                {
                    Point nextP;

                    if     (graph[p.y][p.x] == 'U') nextP = {p.y - 1, p.x};
                    else if(graph[p.y][p.x] == 'L') nextP = {p.y, p.x - 1};
                    else if(graph[p.y][p.x] == 'D') nextP = {p.y + 1, p.x};
                    else if(graph[p.y][p.x] == 'R') nextP = {p.y, p.x + 1};

                    Point ParentP = getParent(parent, p), ParentNextP = getParent(parent, nextP);

                    if(ParentP == ParentNextP) break;

                    parent[ParentP.y][ParentP.x] = ParentNextP;

                    p = nextP;
                }
            }
        }
    }
    free(graph);

    bool (*used)[M] = (bool (*)[M])calloc(N * M, sizeof(bool));
    for (u16 i = 0; i < N; i++)
    {
        for (u16 j = 0; j < M; j++)
        {
            Point p = getParent(parent, {i, j});

            if(used[p.y][p.x] == false)
            {
                count++;
                used[p.y][p.x] = true;
            }
        }
    }
    free(used);
    for (u16 i = 0; i < N; i++) delete[] parent[i];
    delete parent;

    printf("%u\n", count);

}