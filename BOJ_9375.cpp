#include <iostream>
#include <string>
#include <queue>
#include <map>

typedef unsigned int u32;

using namespace std;

int main()
{
    u32 n, TC;
    scanf(" %u", &TC);

    while(TC--)
    {
        map<string, u32> mp; 
        queue<string> que;
        u32 sum = 1;

        scanf(" %u", &n);

        while(n--)
        {
            string tmp;
            string str;

            cin >> tmp;
            cin >> str;

            auto iter = mp.find(str);

            if (iter != mp.end())
            {
                (*iter).second++;
            }
            else
            {
                mp.insert(make_pair(str, 1));
                que.push(str);
            }
        }

        u32 size = que.size();

        for (u32 i = 0; i < size; i++)
        {
            sum *= (*mp.find(que.front())).second + 1;
            que.pop();
        }

        sum--;

        printf("%u\n", sum);
    }
}