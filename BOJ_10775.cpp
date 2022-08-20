#include <cstdio>

typedef unsigned int u32;

u32 find(u32* parent, u32 n);

int main()
{
    u32 G, P;
    u32 count = 0;
    u32* parent;
    bool flag = true;

    scanf(" %u", &G);
    scanf(" %u", &P);

    parent = new u32[G + 1];

    for (u32 i = 0; i <= G; i++) parent[i] = i;

    while(P--)
    {
        u32 g_i;

        scanf(" %u", &g_i);

        if(flag)
        {
            u32 root = find(parent, g_i);

            if(root != 0)
            {
                parent[root] = root - 1;
                count++;
            }
            else
            {
                flag = false;
            }
        }
    }

    printf("%u\n", count);

    delete[] parent;
}

u32 find(u32* parent, u32 n)
{
    if(parent[n] == n) return n;
    else return parent[n] = find(parent, parent[n]);
}