#include <cstdio>
#include <cstring>
#include <queue>
#include <malloc.h>

typedef unsigned int u32;

typedef struct _point
{
    u32 y;
    u32 x;
} point;

using namespace std;

int main()
{
    u32 TC;
    scanf(" %u", &TC);

    for (u32 tc = 0; tc < TC; tc++)
    {
        u32 h, w;
        u32 result = 0;
        bool keys[26] = { false };
        queue<point> locked[26];
        queue<point> que;
        char keyStr[30];

        scanf(" %u %u", &h, &w);

        char (*map)[w + 1] = (char (*)[w + 1])malloc(h * (w + 1) * sizeof(char));
        bool (*visited)[w] = (bool (*)[w])calloc(h * w, sizeof(bool));
        
        for (u32 i = 0; i < h; i++) scanf(" %s", map[i]);
        scanf(" %s", keyStr);

        if(keyStr[0] != '0') for (u32 i = 0; i < strlen(keyStr); i++) keys[keyStr[i] - 'a'] = true;

        for (u32 i = 0; i < w; i++)
        {
            if      (map[0][i] == '.') que.push({0, i}), visited[0][i] = true;
            else if (map[0][i] == '$') que.push({0, i}), result++, visited[0][i] = true;
            else if (0 <= map[0][i] - 'a' && map[0][i] - 'a' < 26) que.push({0, i}), keys[map[0][i] - 'a'] = true;
            else if (0 <= map[0][i] - 'A' && map[0][i] - 'A' < 26) locked[map[0][i] - 'A'].push({0, i});

            if      (map[h - 1][i] == '.') que.push({h - 1, i}), visited[h - 1][i] = true;
            else if (map[h - 1][i] == '$') que.push({h - 1, i}), result++, visited[h - 1][i] = true;
            else if (0 <= map[h - 1][i] - 'a' && map[h - 1][i] - 'a' < 26) que.push({h - 1, i}), keys[map[h - 1][i] - 'a'] = true, visited[h - 1][i] = true;
            else if (0 <= map[h - 1][i] - 'A' && map[h - 1][i] - 'A' < 26) locked[map[h - 1][i] - 'A'].push({h - 1, i}), visited[h - 1][i] = true;
        }

        for (u32 i = 1; i < h - 1; i++)
        {
            if      (map[i][0] == '.') que.push({i, 0}), visited[i][0] = true;
            else if (map[i][0] == '$') que.push({i, 0}), result++, visited[i][0] = true;
            else if (0 <= map[i][0] - 'a' && map[i][0] - 'a' < 26) que.push({i, 0}), keys[map[i][0] - 'a'] = true, visited[i][0] = true;
            else if (0 <= map[i][0] - 'A' && map[i][0] - 'A' < 26) locked[map[i][0] - 'A'].push({i, 0}), visited[i][0] = true;

            if      (map[i][w - 1] == '.') que.push({i, w - 1}), visited[i][w - 1] = true;
            else if (map[i][w - 1] == '$') que.push({i, w - 1}), result++, visited[i][w - 1] = true;
            else if (0 <= map[i][w - 1] - 'a' && map[i][w - 1] - 'a' < 26) que.push({i, w - 1}), keys[map[i][w - 1] - 'a'] = true, visited[i][w - 1] = true;
            else if (0 <= map[i][w - 1] - 'A' && map[i][w - 1] - 'A' < 26) locked[map[i][w - 1] - 'A'].push({i, w - 1}), visited[i][w - 1] = true;
        }

        do
        {
            if(!que.empty())
            {
                point p = que.front();
                que.pop();

                if(p.y != 0 && visited[p.y - 1][p.x] == false)
                {
                    if      (map[p.y - 1][p.x] == '.') que.push({p.y - 1, p.x}), visited[p.y - 1][p.x] = true;
                    else if (map[p.y - 1][p.x] == '$') que.push({p.y - 1, p.x}), result++, visited[p.y - 1][p.x] = true;
                    else if (0 <= map[p.y - 1][p.x] - 'a' && map[p.y - 1][p.x] - 'a' < 26) que.push({p.y - 1, p.x}), keys[map[p.y - 1][p.x] - 'a'] = true, visited[p.y - 1][p.x] = true;
                    else if (0 <= map[p.y - 1][p.x] - 'A' && map[p.y - 1][p.x] - 'A' < 26) locked[map[p.y - 1][p.x] - 'A'].push({p.y - 1, p.x}), visited[p.y - 1][p.x] = true;
                }
                if(p.x != 0 && visited[p.y][p.x - 1] == false)
                {
                    if      (map[p.y][p.x - 1] == '.') que.push({p.y, p.x - 1}), visited[p.y][p.x - 1] = true;
                    else if (map[p.y][p.x - 1] == '$') que.push({p.y, p.x - 1}), result++, visited[p.y][p.x - 1] = true;
                    else if (0 <= map[p.y][p.x - 1] - 'a' && map[p.y][p.x - 1] - 'a' < 26) que.push({p.y, p.x - 1}), keys[map[p.y][p.x - 1] - 'a'] = true, visited[p.y][p.x - 1] = true;
                    else if (0 <= map[p.y][p.x - 1] - 'A' && map[p.y][p.x - 1] - 'A' < 26) locked[map[p.y][p.x - 1] - 'A'].push({p.y, p.x - 1}), visited[p.y][p.x - 1] = true;
                }
                if(p.y != h - 1 && visited[p.y + 1][p.x] == false)
                {
                    if      (map[p.y + 1][p.x] == '.') que.push({p.y + 1, p.x}), visited[p.y + 1][p.x] = true;
                    else if (map[p.y + 1][p.x] == '$') que.push({p.y + 1, p.x}), result++, visited[p.y + 1][p.x] = true;
                    else if (0 <= map[p.y + 1][p.x] - 'a' && map[p.y + 1][p.x] - 'a' < 26) que.push({p.y + 1, p.x}), keys[map[p.y + 1][p.x] - 'a'] = true, visited[p.y + 1][p.x] = true;
                    else if (0 <= map[p.y + 1][p.x] - 'A' && map[p.y + 1][p.x] - 'A' < 26) locked[map[p.y + 1][p.x] - 'A'].push({p.y + 1, p.x}), visited[p.y + 1][p.x] = true;
                }
                if(p.x != w - 1 && visited[p.y][p.x + 1] == false)
                {
                    if      (map[p.y][p.x + 1] == '.') que.push({p.y, p.x + 1}), visited[p.y][p.x + 1] = true;
                    else if (map[p.y][p.x + 1] == '$') que.push({p.y, p.x + 1}), result++, visited[p.y][p.x + 1] = true;
                    else if (0 <= map[p.y][p.x + 1] - 'a' && map[p.y][p.x + 1] - 'a' < 26) que.push({p.y, p.x + 1}), keys[map[p.y][p.x + 1] - 'a'] = true, visited[p.y][p.x + 1] = true;
                    else if (0 <= map[p.y][p.x + 1] - 'A' && map[p.y][p.x + 1] - 'A' < 26) locked[map[p.y][p.x + 1] - 'A'].push({p.y, p.x + 1}), visited[p.y][p.x + 1] = true;
                }
            }

            for(u32 i = 0; i < 26; i++)
            {
                if(keys[i] == true)
                {
                    while(!locked[i].empty())
                    {
                        que.push(locked[i].front());
                        locked[i].pop();
                    }
                }
            }

        } while (!que.empty());

        printf("%u\n", result);

        free(visited);
        free(map);
    }
}