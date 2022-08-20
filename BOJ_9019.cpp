#include <iostream>
#include <queue>
#include <string>

typedef unsigned int u32;

using namespace std;

typedef struct _entry
{
    u32 num;
    u32 count;
} entry;

string getCommand(u32 A, u32 B);

int main()
{
    u32 n;
    scanf(" %u", &n);

    while(n--)
    {
        u32 A, B;
        scanf(" %u %u", &A, &B);
        cout << getCommand(A, B) << '\n';
    }
}

string getCommand(u32 A, u32 B)
{
    pair<u32, char> DP[10000] = {};

    queue<entry> que;
    que.push({A, 0});
    DP[A] = {0, 1};

    while(true)
    {
        entry tmp = que.front();
        que.pop();
        u32 num = tmp.num;

        if (num == B)
        {
            u32 count = tmp.count;
            string str;
            str.resize(count);

            while(count--)
            {
                str[count] = DP[num].second;
                num = DP[num].first;
            }

            return str;
        }

        u32 D = (num * 2) % 10000;
        u32 S = (num != 0)? num - 1 : 9999;
        u32 L = num / 1000 + (num % 1000) * 10;
        u32 R = (num % 10) * 1000 + num / 10;

        if (!DP[D].second) que.push({D, tmp.count + 1}), DP[D] = {num, 'D'};
        if (!DP[S].second) que.push({S, tmp.count + 1}), DP[S] = {num, 'S'};
        if (!DP[L].second) que.push({L, tmp.count + 1}), DP[L] = {num, 'L'};
        if (!DP[R].second) que.push({R, tmp.count + 1}), DP[R] = {num, 'R'};
    }
}