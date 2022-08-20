#include <cstdio>
#include <memory.h>
#include <queue>
#include <stack>

typedef unsigned int u32;

typedef struct _entry
{
    u32 num;
    u32 count;
} entry;

using namespace std;

int main()
{
    u32 N;
    queue<entry> que;
    static u32 stage[1000001];
    static u32 previousNum[1000001] = { 0 };

    scanf(" %u", &N);

    memset(stage, 0xFF, 1000001 * sizeof(u32));

    que.push({N, 0});
    stage[N] = 0;

    while(!que.empty())
    {
        entry tmp = que.front();
        que.pop();

        if(tmp.num == 1) break;

        if(tmp.num != 0 && tmp.count + 1 < stage[tmp.num - 1])
        {
            previousNum[tmp.num - 1] = tmp.num;
            stage[tmp.num - 1] = tmp.count + 1;
            que.push({tmp.num - 1, tmp.count + 1});
        }
        if(tmp.num % 2 == 0 && tmp.count + 1 < stage[tmp.num / 2])
        {
            previousNum[tmp.num / 2] = tmp.num;
            stage[tmp.num / 2] = tmp.count + 1;
            que.push({tmp.num / 2, tmp.count + 1});
        }
        if(tmp.num % 3 == 0 && tmp.count + 1 < stage[tmp.num / 3])
        {
            previousNum[tmp.num / 3] = tmp.num;
            stage[tmp.num / 3] = tmp.count + 1;
            que.push({tmp.num / 3, tmp.count + 1});
        }
    }

    printf("%u\n", stage[1]);
    u32 init = 1;
    stack<u32> stk;
    stk.push(1);
    while(previousNum[init]) stk.push(previousNum[init]), init = previousNum[init];
    while(!stk.empty()) printf("%u ", stk.top()), stk.pop();
    printf("\n");
}